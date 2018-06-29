/*******************************************************************************************************
*  Copyright 2017 Alliance for Sustainable Energy, LLC
*
*  NOTICE: This software was developed at least in part by Alliance for Sustainable Energy, LLC
*  (�Alliance�) under Contract No. DE-AC36-08GO28308 with the U.S. Department of Energy and the U.S.
*  The Government retains for itself and others acting on its behalf a nonexclusive, paid-up,
*  irrevocable worldwide license in the software to reproduce, prepare derivative works, distribute
*  copies to the public, perform publicly and display publicly, and to permit others to do so.
*
*  Redistribution and use in source and binary forms, with or without modification, are permitted
*  provided that the following conditions are met:
*
*  1. Redistributions of source code must retain the above copyright notice, the above government
*  rights notice, this list of conditions and the following disclaimer.
*
*  2. Redistributions in binary form must reproduce the above copyright notice, the above government
*  rights notice, this list of conditions and the following disclaimer in the documentation and/or
*  other materials provided with the distribution.
*
*  3. The entire corresponding source code of any redistribution, with or without modification, by a
*  research entity, including but not limited to any contracting manager/operator of a United States
*  National Laboratory, any institution of higher learning, and any non-profit organization, must be
*  made publicly available under this license for as long as the redistribution is made available by
*  the research entity.
*
*  4. Redistribution of this software, without modification, must refer to the software by the same
*  designation. Redistribution of a modified version of this software (i) may not refer to the modified
*  version by the same designation, or by any confusingly similar designation, and (ii) must refer to
*  the underlying software originally provided by Alliance as �System Advisor Model� or �SAM�. Except
*  to comply with the foregoing, the terms �System Advisor Model�, �SAM�, or any confusingly similar
*  designation may not be used to refer to any modified version of this software or any modified
*  version of the underlying software originally provided by Alliance without the prior written consent
*  of Alliance.
*
*  5. The name of the copyright holder, contributors, the United States Government, the United States
*  Department of Energy, or any of their employees may not be used to endorse or promote products
*  derived from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
*  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
*  FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER,
*  CONTRIBUTORS, UNITED STATES GOVERNMENT OR UNITED STATES DEPARTMENT OF ENERGY, NOR ANY OF THEIR
*  EMPLOYEES, BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
*  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
*  IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
*  THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************************************/

#include <algorithm>
#include <cmath>
#include "interconnect.h"
#include "htf_props.h"

double pi = acos(-1.);
double T_ref_K = 298.150;
int NA_cpnt = -1;

IntcOutputs::IntcOutputs() {
    heat_loss = 0;
    temp_drop = 0;
    temp_out = 0;
    temp_ave = 0;
    pressure_drop = 0;
    pressure_out = 0;
    pressure_ave = 0;
    internal_energy = 0;
}

double WallThickness(double d_in) {
    // regression of Wagner-2011 Table 9 values with an R^2=1.000
    return 0.0194*d_in;
}

double MinorPressureDrop(double vel, double rho, double k) {
    return k * (vel * vel) * rho / 2;
}

double MajorPressureDrop(double vel, double rho, double ff, double l, double d) {
// Darcy Weisbach pressure drop for an incompressible fluid using a Darcy friction factor
    if (d <= 0) throw std::invalid_argument("The inner diameter must be greater than 0.");

    return ff * (vel * vel) * l * rho / (2 * d);
}

double FrictionFactor(double rel_rough, double Re) {
    if (Re < 2100) {  // laminar flow
        return 64 / Re;
    }
    else if(Re < 4000) {  // transitional flow
        // see Cheng, N.S. 2008 "Formulas for friction factors in transitional regions" for non-iterative solution
        return FricFactor_Iter(rel_rough, Re);
    }
    else {  // turbulent flow
        // Calculates according to Zigrang, Sylvester 1982 for Re = 4e3 to 1e8 and e/D = 4e-5 to 5e-2
        return pow(-2.0*log10(rel_rough / 3.7 - 5.02 / Re * log10(rel_rough / 3.7 - 5.02 / Re *
            log10(rel_rough / 3.7 + 13.0 / Re))), -2);
    }
}

double FricFactor_Iter(double rel_rough, double Re) {
// Uses an iterative method to solve the implicit Colebrook friction factor function.
// Taken from Piping loss model

    double Test, TestOld, X, Xold, Slope;
    double Acc = .01; //0.0001
    int NumTries;

    if (Re < 2750.) {
        return 64. / std::max(Re, 1.0);
    }

    X = 33.33333;  //1. / 0.03
    TestOld = X + 2. * log10(rel_rough / 3.7 + 2.51 * X / Re);
    Xold = X;
    X = 28.5714;  //1. / (0.03 + 0.005)
    NumTries = 0;

    while (NumTries < 21) {
        NumTries++;
        Test = X + 2 * log10(rel_rough / 3.7 + 2.51 * X / Re);
        if (fabs(Test - TestOld) <= Acc) {
            return 1. / (X * X);
        }

        Slope = (Test - TestOld) / (X - Xold);
        Xold = X;
        TestOld = Test;
        X = std::max((Slope * X - Test) / Slope, 1.e-5);
    }

    //call Messages(-1," Could not find friction factor solution",'Warning',0,250) 
    return 0;
}


//double Re(double rho, double vel, double d, double mu) {
//// Reynold's Number
//    return rho * vel * d / mu;
//}


intc_cpnt::intc_cpnt(double k = 0, double d = 0, double l = 0, double rough = 0, double u = 0,
    double mc = 0, CpntType type = CpntType::Fitting)
    :k_(k),
    d_in_(d),
    l_(l),
    rough_(rough),
    hl_coef_(u),
    mc_(mc),
    wall_thick_(0),
    Type(type),
    OuterSurfArea_valid_(false),
    OuterSurfArea_(0),
    FlowArea_valid_(false),
    FlowArea_(0),
    FluidVolume_valid_(false),
    FluidVolume_(0)
{
    if (k_ < 0) throw std::invalid_argument("The minor loss coefficient (K) cannot be less than 0.");
    if (d_in_ < 0) throw std::invalid_argument("The inner diameter (D_in) cannot be less than 0.");
    if (l_ < 0) throw std::invalid_argument("The length (L) cannot be less than 0.");
    if (rough_ < 0) throw std::invalid_argument("The relative roughness cannot be less than 0.");
    if (hl_coef_ < 0) throw std::invalid_argument("The heat loss coefficient (U) cannot be less than 0.");
    if (mc_ < 0) throw std::invalid_argument("The heat capacity cannot be less than 0.");

    setWallThick(WallThickness(d_in_));
}

intc_cpnt::~intc_cpnt()
{
}

double intc_cpnt::getK() const {
    return k_;
}

void intc_cpnt::setK(double k) {
    if (k >= 0)
    {
        k_ = k;
    }
    else {
        throw std::invalid_argument("The minor loss coefficient (K) cannot be less than 0.");
    }
}

double intc_cpnt::getD() const {
    return d_in_;
}

void intc_cpnt::setD(double d) {
    if (d >= 0)
    {
        d_in_ = d;
        OuterSurfArea_valid_ = false;
    }
    else {
        throw std::invalid_argument("The inner diameter (D_in) cannot be less than 0.");
    }
}

double intc_cpnt::getLength() const {
    return l_;
}

void intc_cpnt::setLength(double l) {
    if (l >= 0)
    {
        l_ = l;
        OuterSurfArea_valid_ = false;
    }
    else {
        throw std::invalid_argument("The length (L) cannot be less than 0.");
    }
}

double intc_cpnt::getRelRough() const {
    return rough_;
}

void intc_cpnt::setRelRough(double rough) {
    if (rough >= 0)
    {
        rough_ = rough;
    }
    else {
        throw std::invalid_argument("The relative roughness cannot be less than 0.");
    }
}

double intc_cpnt::getHLCoef() const {
    return hl_coef_;
}

void intc_cpnt::setHLCoef(double u) {
    if (u >= 0)
    {
        hl_coef_ = u;
    }
    else {
        throw std::invalid_argument("The heat loss coefficient (U) cannot be less than 0.");
    }
}

double intc_cpnt::getHeatCap() const {
    return mc_;
}

void intc_cpnt::setHeatCap(double mc) {
    if (mc >= 0)
    {
        mc_ = mc;
    }
    else {
        throw std::invalid_argument("The heat capacity cannot be less than 0.");
    }
}

double intc_cpnt::getWallThick() const {
    return wall_thick_;
}

void intc_cpnt::setWallThick(double wall_thick) {
    if (wall_thick >= 0)
    {
        wall_thick_ = wall_thick;
    }
    else {
        throw std::invalid_argument("The wall thickness cannot be less than 0.");
    }
}

CpntType intc_cpnt::getType() const {
    return Type;
}

double intc_cpnt::getOuterSurfArea() {
    if (!OuterSurfArea_valid_) { calcOuterSurfArea(); }
    return OuterSurfArea_;
}

void intc_cpnt::calcOuterSurfArea() {
    OuterSurfArea_ = pi * (d_in_ + 2*wall_thick_) * l_;
    OuterSurfArea_valid_ = true;
}

double intc_cpnt::getFlowArea() {
    if (!FlowArea_valid_) { calcFlowArea(); }
    return FlowArea_;
}

void intc_cpnt::calcFlowArea() {
    FlowArea_ = pi * (d_in_ * d_in_) / 4;
    FlowArea_valid_ = true;
}

double intc_cpnt::getFluidVolume() {
    if (!FluidVolume_valid_) { calcFluidVolume(); }
    return FluidVolume_;
}

void intc_cpnt::calcFluidVolume() {
    FluidVolume_ = pi * (d_in_ * d_in_) / 4. * l_;
    FluidVolume_valid_ = true;
}

double intc_cpnt::HeatLoss(double T_cpnt, double T_db) {
    double A = getOuterSurfArea();  // fun needed b/c area is not always valid
    return hl_coef_ * A * (T_cpnt - T_db);
}

double intc_cpnt::TempDrop(HTFProperties *fluidProps, double m_dot, double T_in, double heatLoss) {
    double cp = fluidProps->Cp(T_in) * 1000;  // J/kg-K
    return heatLoss / (m_dot * cp);   // positive value means T_out < T_in
}

double intc_cpnt::TempDrop(HTFProperties *fluidProps, double m_dot, double T_in, double T_cpnt, double T_db) {
    double cp = fluidProps->Cp(T_in) * 1000;  // J/kg-K
    return HeatLoss(T_cpnt, T_db) / (m_dot * cp);   // positive value means T_out < T_in
}

double intc_cpnt::PressureDrop(HTFProperties *fluidProps, double m_dot, double T_htf_ave, double P_htf_ave) {
    double rho = fluidProps->dens(T_htf_ave, P_htf_ave);
    double vel = m_dot / ( rho * getFlowArea() );
    double Re, ff;

    switch (Type)
    {
        case CpntType::Fitting:
            return MinorPressureDrop(vel, rho, k_);
        case CpntType::Pipe:
            Re = fluidProps->Re(T_htf_ave, P_htf_ave, vel, d_in_);
            ff = FrictionFactor(rough_ / d_in_, Re);
            return MajorPressureDrop(vel, rho, ff, l_, d_in_);
        case CpntType::Flex_Hose:
            // TODO : Differentiate this pressure drop relation for flex hoses
            Re = fluidProps->Re(T_htf_ave, P_htf_ave, vel, d_in_);
            ff = FrictionFactor(rough_ / d_in_, Re);
            return MajorPressureDrop(vel, rho, ff, l_, d_in_);
        default:
            throw std::invalid_argument("This component type has no pressure drop calculation.");
    }
}

double intc_cpnt::InternalEnergy(HTFProperties *fluidProps, double T_cpnt, double T_htf_ave, double P_htf_ave) {
    double cp = fluidProps->Cp(T_htf_ave) * 1000;  // J/kg-K
    return (getFluidVolume() * fluidProps->dens(T_htf_ave, P_htf_ave) * cp +
        getHeatCap()) * (T_cpnt - T_ref_K);
}

IntcOutputs intc_cpnt::State(HTFProperties *fluidProps, double m_dot, double T_in, double T_cpnt, double T_db, double P_htf_ave) {
    IntcOutputs output;
    output.heat_loss = HeatLoss(T_cpnt, T_db);
    output.temp_drop = TempDrop(fluidProps, m_dot, T_in, output.heat_loss);
    output.temp_out = T_in - output.temp_drop;
    output.temp_ave = (T_in + output.temp_out) / 2;
    output.pressure_drop = PressureDrop(fluidProps, m_dot, output.temp_ave, P_htf_ave);
    output.pressure_out = P_htf_ave - output.pressure_drop / 2;  // just an approximation to fill an output
    output.pressure_ave = P_htf_ave;
    output.internal_energy = InternalEnergy(fluidProps, T_cpnt, output.temp_ave, P_htf_ave);

    return output;
}



interconnect::interconnect()
    :N_cpnts_(0),
    Length_valid_(false),
    l_(0),
    HeatCap_valid_(false),
    mc_(0),
    OuterSurfArea_valid_(false),
    OuterSurfArea_(0),
    FluidVolume_valid_(false),
    FluidVolume_(0)
{
}

interconnect::interconnect(HTFProperties *fluidProps, double *k, double *d, double *l, double *rel_rough, double *u, double *mc, double *type, int n_cpnts)
    :N_cpnts_(0),
    Length_valid_(false),
    l_(0),
    HeatCap_valid_(false),
    mc_(0),
    OuterSurfArea_valid_(false),
    OuterSurfArea_(0),
    FluidVolume_valid_(false),
    FluidVolume_(0)
{
    import_cpnts(k, d, l, rel_rough, u, mc, type, n_cpnts);
    setFluidProps(fluidProps);
}

interconnect::~interconnect()
{
}

void interconnect::import_cpnts(double *k, double *d, double *l, double *rel_rough, double *u, double *mc, double *type, int num_cpnts)
{
    std::size_t max_cpnts = num_cpnts;
    std::size_t n_cpnts = 0;  // double check number of components
    while (k[n_cpnts] != NA_cpnt && n_cpnts < max_cpnts) { n_cpnts++; }

    if (!cpnts.empty()) { cpnts.clear(); }
    cpnts.reserve(n_cpnts);

    intc_cpnt cpnt;
    for (int i = 0; i < n_cpnts; i++) {
        if (type[i] < 0 || type[i] >= static_cast<int>(CpntType::FINAL_ENTRY)) {
            throw std::invalid_argument("The component type is out of range at index" + std::to_string(i));
        }
        cpnt = intc_cpnt(k[i], d[i], l[i], rel_rough[i], u[i], mc[i], static_cast<CpntType>((int)type[i]));
        cpnts.push_back(cpnt);
        N_cpnts_++;
        l_ += cpnt.getLength();
        mc_ += cpnt.getHeatCap();
        OuterSurfArea_ += cpnt.getOuterSurfArea();
        FluidVolume_ += cpnt.getFluidVolume();
    }
    Length_valid_ = true;
    HeatCap_valid_ = true;
    OuterSurfArea_valid_ = true;
    FluidVolume_valid_ = true;
}

void interconnect::resetValues() {
    cpnts.clear();
    N_cpnts_ = 0;
    FluidProps_ = NULL;
    Length_valid_ = false;
    l_ = 0;
    HeatCap_valid_ = false;
    mc_ = 0;
    OuterSurfArea_valid_ = false;
    OuterSurfArea_ = 0;
    FluidVolume_valid_ = false;
    FluidVolume_ = 0;
}

void interconnect::setFluidProps(HTFProperties *fluidProps) {
    FluidProps_ = fluidProps;
}

int interconnect::getNcpnts() {
    return N_cpnts_;
}

double interconnect::getK(std::size_t cpnt) const
{
    return cpnts.at(cpnt).getK();
}

double interconnect::getD(std::size_t cpnt) const
{
    return cpnts.at(cpnt).getD();
}

double interconnect::getLength() {
    if (!Length_valid_) { calcLength(); }
    return l_;
}

double interconnect::getLength(std::size_t cpnt) const
{
    return cpnts.at(cpnt).getLength();
}

void interconnect::calcLength() {
    l_ = 0;
    for (std::vector<intc_cpnt>::iterator it = cpnts.begin(); it < cpnts.end(); ++it) {
        l_ += it->getLength();  // intc_cpnt::getLength()
    }
    Length_valid_ = true;
}

double interconnect::getRelRough(std::size_t cpnt) const
{
    return cpnts.at(cpnt).getRelRough();
}

double interconnect::getHLCoef(std::size_t cpnt) const
{
    return cpnts.at(cpnt).getHLCoef();
}

double interconnect::getHeatCap() {
    if (!HeatCap_valid_) { calcHeatCap(); }
    return mc_;
}

double interconnect::getHeatCap(std::size_t cpnt) const
{
    return cpnts.at(cpnt).getHeatCap();
}

void interconnect::calcHeatCap() {
    mc_ = 0;
    for (std::vector<intc_cpnt>::iterator it = cpnts.begin(); it < cpnts.end(); ++it) {
        mc_ += it->getHeatCap();  // intc_cpnt::getHeatCap()
    }
    HeatCap_valid_ = true;
}

CpntType interconnect::getType(std::size_t cpnt) const {
    return cpnts.at(cpnt).getType();
}

double interconnect::getOuterSurfArea() {
    if (!OuterSurfArea_valid_) { calcOuterSurfArea(); }
    return OuterSurfArea_;
}

double interconnect::getOuterSurfArea(std::size_t cpnt) {
    return cpnts.at(cpnt).getOuterSurfArea();
}

void interconnect::calcOuterSurfArea() {
    OuterSurfArea_ = 0;
    for (std::vector<intc_cpnt>::iterator it = cpnts.begin(); it < cpnts.end(); ++it) {
        OuterSurfArea_ += it->getOuterSurfArea();  // intc_cpnt::getOuterSurfArea()
    }
    OuterSurfArea_ = true;
}

double interconnect::getFlowArea(std::size_t cpnt) {
    return cpnts.at(cpnt).getFlowArea();
}

double interconnect::getFluidVolume() {
    if (!FluidVolume_valid_) { calcFluidVolume(); }
    return FluidVolume_;
}

double interconnect::getFluidVolume(std::size_t cpnt) {
    return cpnts.at(cpnt).getFluidVolume();
}

void interconnect::calcFluidVolume() {
    FluidVolume_ = 0;
    for (std::vector<intc_cpnt>::iterator it = cpnts.begin(); it < cpnts.end(); ++it) {
        FluidVolume_ += it->getFluidVolume();  // intc_cpnt::getFluidVolume()
    }
    FluidVolume_valid_ = true;
}

IntcOutputs interconnect::State(double m_dot, double T_in, double T_db, double P_in) {
    IntcOutputs output;
    
    if (N_cpnts_ > 0) {
        IntcOutputs IntcOutput;
        double T_out_prev = T_in;
        double P_out_prev = P_in;

        for (std::vector<intc_cpnt>::iterator it = cpnts.begin(); it < cpnts.end(); ++it) {
            IntcOutput = it->State(FluidProps_, m_dot, T_out_prev, T_out_prev, T_db, P_out_prev);  // intc_cpnt::State()
            output.heat_loss += IntcOutput.heat_loss;
            output.pressure_drop += IntcOutput.pressure_drop;
            output.internal_energy += IntcOutput.internal_energy;

            T_out_prev = IntcOutput.temp_out;
            P_out_prev = P_out_prev - IntcOutput.pressure_drop;
        }
        output.temp_drop = T_in - IntcOutput.temp_out;
        output.temp_out = IntcOutput.temp_out;
        output.temp_ave = (T_in + output.temp_out) / 2;
        output.pressure_out = P_in - output.pressure_drop;
        output.pressure_ave = (P_in + output.pressure_out) / 2;
    }
    else {
        output.heat_loss = 0;
        output.temp_drop = 0;
        output.temp_out = T_in;
        output.temp_ave = T_in;
        output.pressure_drop = 0;
        output.pressure_out = P_in;
        output.pressure_ave = P_in;
        output.internal_energy = 0;
    }
    
    return output;
}


