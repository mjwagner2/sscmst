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

#include "csp_solver_mspt_receiver_222.h"
#include "csp_solver_core.h"

C_mspt_receiver_222::C_mspt_receiver_222()
{
	m_n_panels = -1;

	m_d_rec = std::numeric_limits<double>::quiet_NaN();
	m_h_rec = std::numeric_limits<double>::quiet_NaN();
	m_h_tower = std::numeric_limits<double>::quiet_NaN();
	m_od_tube = std::numeric_limits<double>::quiet_NaN();
	m_th_tube = std::numeric_limits<double>::quiet_NaN();
	m_epsilon = std::numeric_limits<double>::quiet_NaN();
	m_hl_ffact = std::numeric_limits<double>::quiet_NaN();
	m_T_htf_hot_des = std::numeric_limits<double>::quiet_NaN();
	m_T_htf_cold_des = std::numeric_limits<double>::quiet_NaN();
	m_f_rec_min = std::numeric_limits<double>::quiet_NaN();
	m_q_rec_des = std::numeric_limits<double>::quiet_NaN();
	m_rec_su_delay = std::numeric_limits<double>::quiet_NaN();
	m_rec_qf_delay = std::numeric_limits<double>::quiet_NaN();
	m_m_dot_htf_max_frac = std::numeric_limits<double>::quiet_NaN();
	m_A_sf = std::numeric_limits<double>::quiet_NaN();

	m_pipe_loss_per_m = std::numeric_limits<double>::quiet_NaN();
	m_pipe_length_add = std::numeric_limits<double>::quiet_NaN();
	m_pipe_length_mult = std::numeric_limits<double>::quiet_NaN();

	m_id_tube = std::numeric_limits<double>::quiet_NaN();
	m_A_tube = std::numeric_limits<double>::quiet_NaN();
	m_n_t = -1;
	m_n_flux_x = 0;
	m_n_flux_y = 0;

	m_T_salt_hot_target = std::numeric_limits<double>::quiet_NaN();
	m_eta_pump = std::numeric_limits<double>::quiet_NaN();
	m_night_recirc = -1;
	m_hel_stow_deploy = std::numeric_limits<double>::quiet_NaN();

		// Added for csp_solver/tcs wrapper
	m_field_fl = -1;
	error_msg = "";
	m_mat_tube = -1;
	m_flow_type = -1;
    m_crossover_shift = 0;

	m_A_rec_proj = std::numeric_limits<double>::quiet_NaN();
	m_A_node = std::numeric_limits<double>::quiet_NaN();

	m_Q_dot_piping_loss = std::numeric_limits<double>::quiet_NaN();
	m_m_dot_htf_max = std::numeric_limits<double>::quiet_NaN();

	m_itermode = -1;
	m_od_control = std::numeric_limits<double>::quiet_NaN();
	m_eta_field_iter_prev = std::numeric_limits<double>::quiet_NaN();
	m_tol_od = std::numeric_limits<double>::quiet_NaN();
	m_m_dot_htf_des = std::numeric_limits<double>::quiet_NaN();
	m_q_dot_inc_min = std::numeric_limits<double>::quiet_NaN();

	m_mode = -1;
	m_mode_prev = -1;
	m_E_su = std::numeric_limits<double>::quiet_NaN();
	m_E_su_prev = std::numeric_limits<double>::quiet_NaN();
	m_t_su = std::numeric_limits<double>::quiet_NaN();
	m_t_su_prev = std::numeric_limits<double>::quiet_NaN();

	m_flow_pattern = 0;
	m_n_lines = -1;

	m_m_mixed = std::numeric_limits<double>::quiet_NaN();
	m_LoverD = std::numeric_limits<double>::quiet_NaN();
	m_RelRough = std::numeric_limits<double>::quiet_NaN();

	m_is_iscc = false;
	m_cycle_config = 1;

	m_T_amb_low = std::numeric_limits<double>::quiet_NaN();
	m_T_amb_high = std::numeric_limits<double>::quiet_NaN();
	m_P_amb_low = std::numeric_limits<double>::quiet_NaN();
	m_P_amb_high = std::numeric_limits<double>::quiet_NaN();

	m_q_iscc_max = std::numeric_limits<double>::quiet_NaN();
	
	m_ncall = -1;

	//Transient model parameters
	m_is_transient = 0;
	m_is_startup_transient = 0;
	m_rec_tm_mult = std::numeric_limits<double>::quiet_NaN();
	m_u_riser = std::numeric_limits<double>::quiet_NaN();
	m_th_riser = std::numeric_limits<double>::quiet_NaN();
	m_th_downc = std::numeric_limits<double>::quiet_NaN();
	m_piping_loss_coeff = std::numeric_limits<double>::quiet_NaN();
	m_riser_tm_mult = std::numeric_limits<double>::quiet_NaN();
	m_downc_tm_mult = std::numeric_limits<double>::quiet_NaN();
	m_id_riser = std::numeric_limits<double>::quiet_NaN();
	m_od_riser = std::numeric_limits<double>::quiet_NaN();
	m_id_downc = std::numeric_limits<double>::quiet_NaN();
	m_od_downc = std::numeric_limits<double>::quiet_NaN();
	m_Rtot_riser = std::numeric_limits<double>::quiet_NaN();
	m_Rtot_downc = std::numeric_limits<double>::quiet_NaN();
	m_tube_flux_startup = std::numeric_limits<double>::quiet_NaN();
	m_heat_trace_power = std::numeric_limits<double>::quiet_NaN();
	m_preheat_target = std::numeric_limits<double>::quiet_NaN();
	m_startup_target = std::numeric_limits<double>::quiet_NaN();

	m_is_startup_from_solved_profile = 0;
	m_is_enforce_min_startup = 1;

	m_n_elem = 0;
	m_nz_tot = 0;
	m_startup_mode = -1;
	m_startup_mode_initial = -1;
	m_n_call_circ = -1;
	m_n_call_circ_initial = -1;
	m_total_startup_time = std::numeric_limits<double>::quiet_NaN();
	m_total_startup_time_initial = std::numeric_limits<double>::quiet_NaN();
	m_minimum_startup_time = std::numeric_limits<double>::quiet_NaN();
}

void C_mspt_receiver_222::init()
{
	ambient_air.SetFluid(ambient_air.Air);

	// Declare instance of fluid class for FIELD fluid
	if( m_field_fl != HTFProperties::User_defined && m_field_fl < HTFProperties::End_Library_Fluids )
	{
		if( !field_htfProps.SetFluid( m_field_fl ) )
		{
			throw(C_csp_exception("Receiver HTF code is not recognized", "MSPT receiver"));
		}
	}
	else if( m_field_fl == HTFProperties::User_defined )
	{
		// Check that 'm_field_fl_props' is allocated and correct dimensions
		int n_rows = (int)m_field_fl_props.nrows();
		int n_cols = (int)m_field_fl_props.ncols();
		if( n_rows > 2 && n_cols == 7 )
		{
			if( !field_htfProps.SetUserDefinedFluid(m_field_fl_props) )
			{
				error_msg = util::format(field_htfProps.UserFluidErrMessage(), n_rows, n_cols);
				throw(C_csp_exception(error_msg, "MSPT receiver"));
			}
		}
		else
		{
			error_msg = util::format("The user defined field HTF table must contain at least 3 rows and exactly 7 columns. The current table contains %d row(s) and %d column(s)", n_rows, n_cols);
			throw(C_csp_exception(error_msg, "MSPT receiver"));
		}
	}
	else
	{
		throw(C_csp_exception("Receiver HTF code is not recognized", "MSPT receiver"));
	}

	
	// Declare instance of htf class for receiver tube material
	if( m_mat_tube == HTFProperties::Stainless_AISI316 || m_mat_tube == HTFProperties::T91_Steel )
	{
		if( !tube_material.SetFluid(m_mat_tube) )
		{
			throw(C_csp_exception("Tube material code not recognized", "MSPT receiver"));
		}
	}
	else if( m_mat_tube == HTFProperties::User_defined )
	{
		throw(C_csp_exception("Receiver material currently does not accept user defined properties", "MSPT receiver"));
	}
	else
	{
		error_msg = util::format("Receiver material code, %d, is not recognized", m_mat_tube);
		throw(C_csp_exception(error_msg, "MSPT receiver"));
	}

	// Unit Conversions
	m_od_tube /= 1.E3;			//[m] Convert from input in [mm]
	m_th_tube /= 1.E3;			//[m] Convert from input in [mm]
	m_T_htf_hot_des += 273.15;	//[K] Convert from input in [C]
	m_T_htf_cold_des += 273.15;	//[K] Convert from input in [C]
	m_q_rec_des *= 1.E6;		//[W] Convert from input in [MW]

	m_id_tube = m_od_tube - 2 * m_th_tube;			//[m] Inner diameter of receiver tube
	m_A_tube = CSP::pi*m_od_tube / 2.0*m_h_rec;	//[m^2] Outer surface area of each tube
	m_n_t = (int)(CSP::pi*m_d_rec / (m_od_tube*m_n_panels));	// The number of tubes per panel, as a function of the number of panels and the desired diameter of the receiver
	
	int n_tubes = m_n_t * m_n_panels;				//[-] Number of tubes in the system
	m_A_rec_proj = m_od_tube*m_h_rec*n_tubes;		//[m^2] The projected area of the tubes on a plane parallel to the center lines of the tubes
	m_A_node = CSP::pi*m_d_rec / m_n_panels*m_h_rec; //[m^2] The area associated with each node

	m_mode = C_csp_collector_receiver::OFF;					//[-] 0 = requires startup, 1 = starting up, 2 = running
	m_itermode = 1;			//[-] 1: Solve for design temp, 2: solve to match mass flow restriction
	m_od_control = 1.0;			//[-] Additional defocusing for over-design conditions
	m_tol_od = 0.001;		//[-] Tolerance for over-design iteration

	double c_htf_des = field_htfProps.Cp((m_T_htf_hot_des + m_T_htf_cold_des) / 2.0)*1000.0;		//[J/kg-K] Specific heat at design conditions
	m_m_dot_htf_des = m_q_rec_des / (c_htf_des*(m_T_htf_hot_des - m_T_htf_cold_des));					//[kg/s]
	double eta_therm_des = 0.9;
	m_q_dot_inc_min = m_q_rec_des * m_f_rec_min / eta_therm_des;	//[W] Minimum receiver thermal power

	if (m_m_dot_htf_max_frac != m_m_dot_htf_max_frac)
	{
		// if max frac not set, then max mass flow (absolute) needs to be defined
		if (m_m_dot_htf_max != m_m_dot_htf_max)
		{
			throw(C_csp_exception("maximum rec htf mass flow rate not defined", "MSPT receiver"));
		}
		m_m_dot_htf_max /= 3600.0;	//[kg/s] Convert from input in [kg/hr]
	}
	m_m_dot_htf_max = m_m_dot_htf_max_frac * m_m_dot_htf_des;	//[kg/s]

	m_mode_prev = m_mode;
	m_E_su_prev = m_q_rec_des * m_rec_qf_delay;	//[W-hr] Startup energy
	m_t_su_prev = m_rec_su_delay;				//[hr] Startup time requirement
	m_eta_field_iter_prev = 1.0;				//[-] Set to largest possible value

	m_T_salt_hot_target += 273.15;			//[K] convert from C
	
	// 8.10.2015 twn: Calculate constant thermal losses to the environment
	//if(m_pipe_loss_per_m > 0.0 && m_pipe_length_mult > 0.0)
	//	m_Q_dot_piping_loss = m_pipe_loss_per_m*(m_h_tower*m_pipe_length_mult + m_pipe_length_add);		//[Wt]
	//else
	//	m_Q_dot_piping_loss = 0.0;



	// *******************************************************************
	// *******************************************************************
	//      Allocate the input array for the flux map!?!?!??! (line 418 type222)
	// *******************************************************************
	// *******************************************************************

	std::string flow_msg;
	if( !CSP::flow_patterns(m_n_panels, m_crossover_shift, m_flow_type, m_n_lines, m_flow_pattern, &flow_msg) )
	{
		throw(C_csp_exception(flow_msg, "MSPT receiver initialization"));
	}

	m_q_dot_inc.resize(m_n_panels);
	m_q_dot_inc.fill(0.0);

	m_T_s_guess.resize(m_n_panels);
	m_T_s_guess.fill(0.0);
	m_T_s.resize(m_n_panels);
	m_T_s.fill(0.0);

	m_T_panel_out_guess.resize(m_n_panels);
	m_T_panel_out.resize(m_n_panels);
	m_T_panel_out_guess.fill(0.0);
	m_T_panel_out.fill(0.0);

	m_T_panel_in_guess.resize(m_n_panels);
	m_T_panel_in_guess.fill(0.0);
	m_T_panel_in.resize(m_n_panels);
	m_T_panel_in.fill(0.0);

	m_T_panel_ave.resize(m_n_panels);
	m_T_panel_ave.fill(0.0);
	m_T_panel_ave_guess.resize(m_n_panels);
	m_T_panel_ave_guess.fill(0.0);

	m_T_film.resize(m_n_panels);
	m_T_film.fill(0.0);

	m_q_dot_conv.resize(m_n_panels);
	m_q_dot_conv.fill(0.0);

	m_q_dot_rad.resize(m_n_panels);
	m_q_dot_rad.fill(0.0);

	m_q_dot_loss.resize(m_n_panels);
	m_q_dot_loss.fill(0.0);

	m_q_dot_abs.resize(m_n_panels);
	m_q_dot_abs.fill(0.0);

	m_m_mixed = 3.2;	//[-] Exponential for calculating mixed convection

	m_LoverD = m_h_rec / m_id_tube;
	m_RelRough = (4.5e-5) / m_id_tube;	//[-] Relative roughness of the tubes. http:www.efunda.com/formulae/fluids/roughness.cfm

	if(m_is_iscc)
	{
		// Set cycle configuration in class
		cycle_calcs.set_cycle_config(m_cycle_config);

		// Get table limits
		cycle_calcs.get_table_range(m_T_amb_low, m_T_amb_high, m_P_amb_low, m_P_amb_high);
	}

	m_ncall = -1;


	//************** Transient model parameters  **************************
	m_th_riser /= 1.E3;				//[m], Riser wall thickness, convert from input in [mm]
	m_th_downc = m_th_riser;		//[m], Downcomer wall thickness, convert from input in [mm]
	m_heat_trace_power *= 1.e3;		//[W/m-length], Heat trace power for riser and downcomer during startup, convert from input in [kW/m]
	m_piping_loss_coeff = fmax(1.e-4, m_piping_loss_coeff);
	m_initial_temperature += 273.15;  // Initial temperature at start of simulation [K], convert from input in [C]
	m_preheat_target += 273.15;		// Preheat target temperature [K], convert from input in [C]
	m_startup_target += 273.15;		// Startup target temperature [K], convert from input in [C]

	// HTF properties
	double rho_htf_inlet = field_htfProps.dens(m_T_htf_cold_des, 1.0);								
	double rho_htf_des = field_htfProps.dens((m_T_htf_hot_des + m_T_htf_cold_des) / 2.0, 1.0);		
	double mu_htf_des = field_htfProps.visc((m_T_htf_hot_des + m_T_htf_cold_des) / 2.0);	
	double rho_tube_des = tube_material.dens((m_T_htf_hot_des + m_T_htf_cold_des) / 2.0, 1.0);
	double c_tube_des = tube_material.Cp((m_T_htf_hot_des + m_T_htf_cold_des) / 2.0)*1000.0;

	// Riser/downcomer sizing, thermal mass, and constant thermal resistance 
	m_id_riser = pow(4.0*m_m_dot_htf_des / rho_htf_inlet / CSP::pi / m_u_riser, 0.5);	// Riser ID [m]
	m_id_downc = m_id_riser;
	m_od_riser = m_id_riser + 2.0 * m_th_riser;				// Riser OD [m]
	m_od_downc = m_id_downc + 2.0 * m_th_downc;				// Downcomer OD [m]
	double tm_riser = m_riser_tm_mult * (0.25*CSP::pi*pow(m_id_riser, 2)*rho_htf_des*c_htf_des + 0.25*CSP::pi*(pow(m_od_riser, 2) - pow(m_id_riser, 2))*rho_tube_des*c_tube_des);	// Thermal mass of riser [J/m/K]
	double tm_downc = m_downc_tm_mult * (0.25*CSP::pi*pow(m_id_downc, 2)*rho_htf_des*c_htf_des + 0.25*CSP::pi*(pow(m_od_downc, 2) - pow(m_id_downc, 2))*rho_tube_des*c_tube_des);	// Thermal mass of downcomer [J/m/K]
	double tm_riser_solid = tm_riser - 0.25*CSP::pi*pow(m_id_riser, 2)*rho_htf_des*c_htf_des;		// Thermal mass of riser tube [J/m/K]
	double tm_downc_solid = tm_downc - 0.25*CSP::pi*pow(m_id_downc, 2)*rho_htf_des*c_htf_des;		// Thermal mass of downcomer tube [J/m/K]	
	m_Rtot_riser = 1.0 / (m_piping_loss_coeff * 0.5 * m_id_riser);  // Riser total thermal resistance between fluid and ambient [K*m/W]
	m_Rtot_downc = 1.0 / (m_piping_loss_coeff * 0.5 * m_id_downc);  // Downcomer total thermal resistance between fluid and ambient [K*m/W]

	// Header sizing 
	double dp_header_fract = 0.1;								// Fraction of panel pressure drop allowable in header
	double L_header = 2.0*(CSP::pi*m_d_rec / m_n_panels);		// Header length [m] = 2 x panel width
	double m_m_dot_head = m_m_dot_htf_des / m_n_lines;			// Mass flow rate through header [kg/s]
	double  ftube_des, Nutube_des, m_id_header, m_th_header, m_od_header;
	ftube_des = Nutube_des = m_id_header = m_th_header = m_od_header = std::numeric_limits<double>::quiet_NaN();
	double utube_des = m_m_dot_htf_des / (m_n_lines * m_n_t*rho_htf_des* m_id_tube * m_id_tube * 0.25 * CSP::pi);	//[m/s] Average velocity of the coolant through the receiver tubes
	double Retube_des = rho_htf_des*utube_des*m_id_tube / mu_htf_des;												//[-] Reynolds number of internal flow for receiver tubes
	CSP::PipeFlow(Retube_des, 4.0, m_LoverD, m_RelRough, Nutube_des, ftube_des);									// Calculate friction factor for receiver tube
	double dp_tube = 0.5*rho_htf_des*ftube_des*pow(utube_des, 2) * (m_h_rec / m_id_tube + 2 * 16.0 + 4 * 30.0);		//[Pa] Tube pressure drop including (2) 45deg. bends and (4) 90deg. bends at design point mass flow
	double dp_header = dp_header_fract * dp_tube;																	// Allowable header pressure drop [Pa]
	calc_header_size(dp_header, m_m_dot_head, rho_htf_des, mu_htf_des, L_header, m_id_header, m_th_header, m_od_header);	// Calculate header size
	double tm_header_tot = L_header * (0.25*CSP::pi*pow(m_id_header, 2)*rho_htf_des*c_htf_des + 0.25*CSP::pi*(pow(m_od_header, 2) - pow(m_id_header, 2))*rho_tube_des*c_tube_des); // Total header thermal mass [J/K]

	// Crossover header sizing
	double tm_header_cross, tm_header_cross_solid, od_header_cross, id_header_cross;
	tm_header_cross = tm_header_cross_solid = od_header_cross = id_header_cross = 0;
	if (m_flow_type == 1 || m_flow_type == 2){
		double th_header_cross = std::numeric_limits<double>::quiet_NaN();
		calc_header_size(dp_header, m_m_dot_head, rho_htf_des, mu_htf_des, m_d_rec, id_header_cross, th_header_cross, od_header_cross);	// Calculate header size
		tm_header_cross = 0.25*CSP::pi*pow(id_header_cross, 2)*rho_htf_des*c_htf_des + 0.25*CSP::pi*(pow(od_header_cross, 2) - pow(id_header_cross, 2))*rho_tube_des*c_tube_des;	// Thermal mass of crossover header tube wall and fluid [J/m/K]
		tm_header_cross_solid = tm_header_cross - 0.25*CSP::pi*pow(id_header_cross, 2)*rho_htf_des*c_htf_des;	// Thermal mass of crossover header tube wall [W/m/K]
	}

	// Receiver tube thermal mass (including inter-panel headers)  [J/m/K]
	double tm_tube = m_rec_tm_mult * (0.25*CSP::pi*pow(m_id_tube, 2)*rho_htf_des*c_htf_des + 0.25*CSP::pi*(pow(m_od_tube, 2) - pow(m_id_tube, 2))*rho_tube_des*c_tube_des + tm_header_tot / m_h_rec / (double)m_n_t);	// Thermal mass of receiver tube and fluid including the inter-panel header [J/m/K]
	double tm_tube_solid = tm_tube - 0.25*CSP::pi*pow(m_id_tube, 2)*rho_htf_des*c_htf_des - (0.25*CSP::pi*pow(m_id_header, 2)*rho_htf_des*c_htf_des)*L_header / m_h_rec / (double)m_n_t;		// Thermal mass of receiver tube including inter-panel header [J/m/K]

	// Set up PDE parameters : dT/dt + lam1*dT/dz + lam2*T = C
	m_n_elem = m_n_panels / m_n_lines + 2;		// Number of flow elements in each flow path: Inter-panel headers are lumped with panels for simplicity
	int nz_panel = 3;						    // Number of axial evaluation points per panel or crossover header
	int nz_tower = 6;							// Number of axial evaluation points per riser or downcomer
	m_nz_tot = nz_panel*m_n_panels / m_n_lines + 2 * nz_tower;	// Total number of axial evaluation points in one flow path
	int crossposition = 0;
	if (m_flow_type == 1 || m_flow_type == 2)	// Flow path contains a crossover header
	{
		m_n_elem = m_n_elem + 1;
		m_nz_tot = m_nz_tot + nz_panel;
		double npq = (double)m_n_panels / 4.;
		int nq1;
		if (m_n_panels % 4 != 0)
			nq1 = (int)floor(npq) + 1;
		else
			nq1 = (int)floor(npq + 1.e-6);
		crossposition = nq1 + 1;		// Location of crossover header in array of all flow elements
	}
	trans_inputs.nelem = m_n_elem;
	trans_inputs.nztot = m_nz_tot;
	trans_inputs.npath = m_n_lines;
	trans_inputs.length.resize(m_n_elem, m_h_rec);	// Total length of each flow element [m]
	trans_inputs.nz.resize(m_n_elem, nz_panel);		// # of axial evaluation points per flow element
	trans_inputs.zpts.resize(m_nz_tot);				// Axial point positions (z = 0 at inlet of each flow element)
	trans_inputs.startpt.resize(m_n_elem);			// Index of first axial position associated with each flow element

	trans_inputs.lam1.resize_fill(m_n_elem, m_n_lines, 0.0);	// Parameter 1 (lam1) [m/s] 
	trans_inputs.lam2.resize_fill(m_n_elem, m_n_lines, 0.0);	// Parameter 2 (lam2) [1/s]
	trans_inputs.cval.resize_fill(m_n_elem, m_n_lines, 0.0);	// Parameter 3 (C) [K/s]
	trans_inputs.Rtube.resize_fill(m_n_elem, m_n_lines, 0.0);	
	trans_inputs.tinit.resize_fill(m_nz_tot, m_n_lines, m_initial_temperature);  // Initial temperature profile [K]
	trans_inputs.tinit_wall.resize_fill(m_nz_tot, m_n_lines, m_initial_temperature);  // Initial wall temperature profile [K]

	m_flowelem_type.resize(m_n_elem, m_n_lines);	// Identifier for each flow element in flow path order: positive integer = receiver panel number, -1 = riser, -2 = downcomer, -3 = crossover header
	m_flowelem_type.fill(0);
	m_tm.resize(m_n_elem, tm_tube);
	m_tm_solid.resize(m_n_elem, tm_tube_solid);
	m_od.resize(m_n_elem, m_od_tube);
	m_id.resize(m_n_elem, m_id_tube);

	// Fill in tube panel positions in flow order
	int k = 0;
	for (int j = 0; j < m_n_panels / m_n_lines; j++)
	{
		k = j + 1;
		if ((m_flow_type == 1 || m_flow_type == 2) && k >= crossposition)	// Panel resides after a crossover header
			k = k + 1;
		for (int i = 0; i < m_n_lines; i++)
			m_flowelem_type.at(k, i) = m_flow_pattern.at(i, j);
	}

	// Fill in riser/downcomer/crossover header parameters
	trans_inputs.length.at(0) = trans_inputs.length.at(m_n_elem - 1) = 0.5*(m_h_tower*m_pipe_length_mult + m_pipe_length_add);
	trans_inputs.nz.at(0) = trans_inputs.nz.at(m_n_elem - 1) = nz_tower;
	m_tm.at(0) = tm_riser;
	m_tm_solid.at(0) = tm_riser_solid;
	m_tm.at(m_n_elem - 1) = tm_downc;
	m_tm_solid.at(m_n_elem - 1) = tm_downc_solid;
	m_od.at(0) = m_od_riser;
	m_od.at(m_n_elem - 1) = m_od_downc;
	m_id.at(0) = m_id_riser;
	m_id.at(m_n_elem - 1) = m_id_downc;
	if (m_flow_type == 1 || m_flow_type == 2)
	{
		trans_inputs.length.at(crossposition) = m_d_rec;
		m_tm.at(crossposition) = tm_header_cross;
		m_tm_solid.at(crossposition) = tm_header_cross_solid;
		m_od.at(crossposition) = od_header_cross;
		m_id.at(crossposition) = id_header_cross;
	}
	for (int i = 0; i < m_n_lines; i++)
	{
		m_flowelem_type.at(0, i) = -1;
		m_flowelem_type.at(m_n_elem - 1, i) = -2;
		if (m_flow_type == 1 || m_flow_type == 2)
			m_flowelem_type.at(crossposition, i) = -3;
	}

	// Set local axial positions
	double dz;
	int s = 0;
	for (int j = 0; j < m_n_elem; j++)
	{
		trans_inputs.startpt.at(j) = s;
		dz = trans_inputs.length.at(j) / (double)(trans_inputs.nz.at(j) - 1);	// Spacing between axial points
		for (int i = 0; i < trans_inputs.nz.at(j); i++)				// Loop over axial positions
			trans_inputs.zpts.at(s + i) = dz * i;
		s = s + trans_inputs.nz.at(j);
	}

	trans_outputs.timeavg_tout = trans_outputs.timeavg_conv_loss = trans_outputs.timeavg_rad_loss = trans_outputs.timeavg_piping_loss = trans_outputs.timeavg_qthermal = trans_outputs.timeavg_qnet = trans_outputs.timeavg_eta_therm = trans_outputs.time_min_tout = ::numeric_limits<double>::quiet_NaN();
	trans_outputs.max_tout = trans_outputs.min_tout = trans_outputs.max_rec_tout = std::numeric_limits<double>::quiet_NaN();
	trans_outputs.timeavg_temp.resize_fill(m_n_elem, m_n_lines, 0.0);

	trans_outputs.t_profile.resize_fill(m_nz_tot, m_n_lines, m_initial_temperature); 
	trans_outputs.t_profile_wall.resize_fill(m_nz_tot, m_n_lines, m_initial_temperature);
	trans_outputs.tube_temp_inlet = trans_outputs.tube_temp_outlet = m_initial_temperature;

	param_inputs.T_amb = param_inputs.T_sky = param_inputs.c_htf = param_inputs.rho_htf = param_inputs.mu_htf = param_inputs.k_htf = param_inputs.Pr_htf = std::numeric_limits<double>::quiet_NaN();
	param_inputs.Tfeval.resize_fill(m_n_elem, m_n_lines, 0.0); param_inputs.Tseval.resize_fill(m_n_elem, m_n_lines, 0.0); param_inputs.qinc.resize_fill(m_n_elem, m_n_lines, 0.0); 

	return;
}

void C_mspt_receiver_222::call(const C_csp_weatherreader::S_outputs &weather, 
	const C_csp_solver_htf_1state &htf_state_in,
	const C_mspt_receiver_222::S_inputs &inputs,
	const C_csp_solver_sim_info &sim_info)
{
	// Increase call-per-timestep counter
	// Converge() sets it to -1, so on first call this line will adjust it = 0
	m_ncall++;
	
	// Get inputs
	double field_eff = inputs.m_field_eff;					//[-]
	const util::matrix_t<double> *flux_map_input = inputs.m_flux_map_input;
		// When this function is called from TCS solver, input_operation_mode should always be == 2
	int input_operation_mode = inputs.m_input_operation_mode;

	if(input_operation_mode < C_csp_collector_receiver::OFF || input_operation_mode > C_csp_collector_receiver::STEADY_STATE)
	{
		error_msg = util::format("Input operation mode must be either [0,1,2], but value is %d", input_operation_mode);
		throw(C_csp_exception(error_msg, "MSPT receiver timestep performance call"));
	}

	// Get sim info 
	double step = sim_info.ms_ts.m_step;			//[s]
	double time = sim_info.ms_ts.m_time;	//[s]

	// Get applicable htf state info
	double T_salt_cold_in = htf_state_in.m_temp;		//[C]

	// Complete necessary conversions/calculations of input variables
	T_salt_cold_in += 273.15;				//[K] Cold salt inlet temp, convert from C
	double P_amb = weather.m_pres*100.0;	//[Pa] Ambient pressure, convert from mbar
	double hour = time / 3600.0;			//[hr] Hour of the year
	double hour_day = (int) hour%24;		//[hr] Hour of the day
	double T_dp = weather.m_tdew + 273.15;	//[K] Dewpoint temperature, convert from C
	double T_amb = weather.m_tdry + 273.15;	//[K] Dry bulb temperature, convert from C
	// **************************************************************************************

	// Read in remaining weather inputs from weather output structure
	double zenith = weather.m_solzen;
	double azimuth = weather.m_solazi;
	double v_wind_10 = weather.m_wspd;
	double I_bn = weather.m_beam;


	int n_flux_y = (int)flux_map_input->nrows();
	if(n_flux_y > 1)
	{
		error_msg = util::format("The Molten Salt External Receiver (Type222) model does not currently support 2-dimensional "
			"flux maps. The flux profile in the vertical dimension will be averaged. NY=%d", n_flux_y);
		csp_messages.add_message(C_csp_messages::WARNING, error_msg);
	}
	int n_flux_x = (int)flux_map_input->ncols();
	m_flux_in.resize(n_flux_x);

	double T_sky = CSP::skytemp(T_amb, T_dp, hour);

	// Set current timestep stored values to NaN so we know that code solved for them
	m_mode = -1;
	m_E_su = std::numeric_limits<double>::quiet_NaN();
	m_t_su = std::numeric_limits<double>::quiet_NaN();

	m_itermode = 1;

	double v_wind = log((m_h_tower + m_h_rec / 2) / 0.003) / log(10.0 / 0.003)*v_wind_10;

	double c_p_coolant, rho_coolant, f, u_coolant, q_conv_sum, q_rad_sum, q_dot_inc_sum, q_dot_inc_min_panel;
	c_p_coolant = rho_coolant = f = u_coolant = q_conv_sum = q_rad_sum = q_dot_inc_sum = q_dot_inc_min_panel = std::numeric_limits<double>::quiet_NaN();
	double eta_therm, m_dot_salt_tot, T_salt_hot_guess, m_dot_salt_tot_ss, T_salt_hot_rec;
	eta_therm = m_dot_salt_tot = T_salt_hot_guess = m_dot_salt_tot_ss = T_salt_hot_rec = std::numeric_limits<double>::quiet_NaN();
	bool rec_is_off = false;
	bool rec_is_defocusing = false;
	double field_eff_adj = 0.0;

	double panel_req_preheat = m_tube_flux_startup * m_od_tube * m_h_rec * m_n_t;					// Panel absorbed solar energy required to meet preheat flux requirement (kW)
	double total_req_preheat = (m_tube_flux_startup * m_od_tube * m_h_rec * m_n_t) * m_n_panels;	// Total absorbed solar energy on all panels (kW) required to meet preheat flux requirement
	bool startup_low_flux = false;

	// ************* Outputs for ISCC model ****************
	double q_thermal_ss = 0.0;
	double f_rec_timestep = 1.0;
	// *****************************************************

	// Do an initial check to make sure the solar position called is valid
	// If it's not, return the output equal to zeros. Also check to make sure
	// the solar flux is at a certain level, otherwise the correlations aren't valid
	if( input_operation_mode == C_csp_collector_receiver::OFF )
	{
		rec_is_off = true;
	}

	if( zenith>(90.0 - m_hel_stow_deploy) || I_bn <= 1.E-6 || (zenith == 0.0 && azimuth == 180.0) )
	{
		if( m_night_recirc == 1 )
		{
			I_bn = 0.0;
		}
		else
		{
			m_mode = C_csp_collector_receiver::OFF;
			rec_is_off = true;
		}
	}

	double T_coolant_prop = (m_T_salt_hot_target + T_salt_cold_in) / 2.0;		//[K] The temperature at which the coolant properties are evaluated. Validated as constant (mjw)
	c_p_coolant = field_htfProps.Cp(T_coolant_prop)*1000.0;						//[J/kg-K] Specific heat of the coolant

	double m_dot_htf_max = m_m_dot_htf_max;
	if( m_is_iscc )
	{
		if( m_ncall == 0 )
		{
			double T_amb_C = fmax(m_P_amb_low, fmin(m_T_amb_high, T_amb - 273.15));
			double P_amb_bar = fmax(m_P_amb_low, fmin(m_P_amb_high, P_amb / 1.E5));
			m_q_iscc_max = cycle_calcs.get_ngcc_data(0.0, T_amb_C, P_amb_bar, ngcc_power_cycle::E_solar_heat_max)*1.E6;	// W-th, convert from MWth
		}

		double m_dot_iscc_max = m_q_iscc_max / (c_p_coolant*(m_T_salt_hot_target - T_salt_cold_in));		// [kg/s]
		m_dot_htf_max = fmin(m_m_dot_htf_max, m_dot_iscc_max);
	}

	double q_abs_sum = 0.0;
	double err_od = 999.0;	// Reset error before iteration

	// 15 continue -> TRNSYS command - replace
	if (field_eff < m_eta_field_iter_prev && m_od_control < 1.0)
	{	// Suggests controller applied defocus, so reset *controller* defocus
		m_od_control = fmin(m_od_control + (1.0 - field_eff / m_eta_field_iter_prev), 1.0);
	}

	do
	{
		if( rec_is_off )
			break;

		field_eff_adj = field_eff*m_od_control;

		// Get the values of the flux from the fluxmap and store them  as flux_in(col, row)
		if( I_bn > 1.0 )
		{
			for( int j = 0; j<n_flux_x; j++ ){
				m_flux_in.at(j) = 0.;
				for( int i = 0; i<n_flux_y; i++ ){
					m_flux_in.at(j) += (*flux_map_input)(i,j)
						* I_bn*field_eff_adj*m_A_sf / 1000. / (CSP::pi*m_h_rec*m_d_rec / (double)n_flux_x);	//[kW/m^2];
				}
			}
		}
		else
		{
			m_flux_in.fill(0.0);
		}

		double n_flux_x_d = (double)m_n_flux_x;
		double n_panels_d = (double)m_n_panels;

		if( m_n_panels >= m_n_flux_x )
		{
			// Translate to the number of panels, so each panel has its own linearly interpolated flux value
			for( int i = 0; i < m_n_panels; i++ )
			{
				double x = (i + 0.5)*n_flux_x_d / n_panels_d;
				double xlow = ceil(i*n_flux_x_d / n_panels_d) - 0.5;
				int high = ceil(i*n_flux_x_d / n_panels_d);
				int low = high - 1;
				if (high > m_n_flux_x - 1) high = 0;
				if (low < 0) low = m_n_flux_x - 1;
				double psp_field = m_flux_in.at(low) + (m_flux_in.at(high) - m_flux_in.at(low)) * (x - xlow);  //[kW/m^2] Average area-specific power for each node

				/*
				double ppos = (n_flux_x_d / n_panels_d*i + n_flux_x_d*0.5 / n_panels_d);
				int flo = (int)floor(ppos);
				int ceiling = (int)ceil(ppos);
				double ind = (int)((ppos - flo) / fmax((double)(ceiling - flo), 1.e-6));
				if( ceiling > m_n_flux_x - 1 ) ceiling = 0;

				double psp_field = (ind*(m_flux_in.at(ceiling) - m_flux_in.at(flo)) + m_flux_in.at(flo));		//[kW/m^2] Average area-specific power for each node
				*/
				m_q_dot_inc.at(i) = m_A_node*psp_field;	//[kW] The power incident on each node

			}
		}
		else
		{
			/*
			The number of panels is always even, therefore the receiver panels are symmetric about the N-S plane.

			The number of flux points may be even or odd. The distribution is assumed to be symmetric
			about North, therefore:
			(a) A distribution with an odd number of points includes a center point (n_flux_x - 1)/2+1
			whose normal faces exactly north
			(b) A distribution with an even number of points includes 2 points n_flux_x/2, n_flux_x/2+1
			which straddle the North vector.
			In either scenario, two points straddle the South vector and no scenario allows a point to fall
			directly on the South vector. Hence, the first and last flux points fall completely on the first
			and last panel, respectively.
			*/

			double leftovers = 0.;
			int index_start = 0; int index_stop = 0;
			double q_flux_sum = 0.0;

			double panel_step = n_flux_x_d / n_panels_d;   //how many flux points are stepped over by each panel?

			for( int i = 0; i<m_n_panels; i++ )
			{
				double panel_pos = panel_step*(i + 1);   //Where does the current panel end in the flux array?

				index_start = (int)floor(panel_step*i);
				index_stop = (int)floor(panel_pos);

				q_flux_sum = 0.;

				for( int j = index_start; j<index_stop + 1; j++ )
				{
					if( j == m_n_flux_x )
					{
						if( leftovers > 0. )
						{
							csp_messages.add_message(C_csp_messages::WARNING, "An error occurred during interpolation of the receiver flux map. The results may be inaccurate! Contact SAM support to resolve this issue.");
						}							

						break;
					}
					if( j == 0 )
					{
						q_flux_sum = m_flux_in.at(j);
						leftovers = 0.;
					}
					else if( j == index_start )
					{
						q_flux_sum += leftovers;
						leftovers = 0.;
					}
					else if( j == index_stop )
					{
						double stop_mult = (panel_pos - floor(panel_pos));
						q_flux_sum += stop_mult * m_flux_in.at(j);
						leftovers = (1 - stop_mult)*m_flux_in.at(j);
					}
					else
					{
						q_flux_sum += m_flux_in[j];
					}
				}
				m_q_dot_inc.at(i) = q_flux_sum * m_A_node / n_flux_x_d*n_panels_d;
			}

		}

		q_dot_inc_min_panel = m_q_dot_inc.at(0);
		q_dot_inc_sum = 0.0;
		for (int i = 0; i < m_n_panels; i++)
		{
			q_dot_inc_sum += m_q_dot_inc.at(i);		//[kW] Total power absorbed by receiver
			q_dot_inc_min_panel = fmin(q_dot_inc_min_panel, m_q_dot_inc.at(i));	//[kW] Minimum power absorbed by any panel
		}

		// Check that total incident power is greater than min fraction * design
		//if (q_dot_inc_sum*1.E3 < m_q_dot_inc_min)
		//	m_mode = C_csp_collector_receiver::OFF;  // Set the startup mode
		//	rec_is_off = true;
		//	break;
		
		// Set guess values
		if( m_night_recirc == 1 )
		{
			m_T_s_guess.fill(m_T_salt_hot_target);		//[K] Guess the temperature for the surface nodes
			m_T_panel_out_guess.fill((m_T_salt_hot_target + T_salt_cold_in) / 2.0);	//[K] Guess values for the fluid temp coming out of the control volume
			m_T_panel_in_guess.fill((m_T_salt_hot_target + T_salt_cold_in) / 2.0);	//[K] Guess values for the fluid temp coming into the control volume
		}
		else
		{
			m_T_s_guess.fill(m_T_salt_hot_target);		//[K] Guess the temperature for the surface nodes
			m_T_panel_out_guess.fill(T_salt_cold_in);	//[K] Guess values for the fluid temp coming out of the control volume
			m_T_panel_in_guess.fill(T_salt_cold_in);	//[K] Guess values for the fluid temp coming into the control volume
		}

		double c_guess = field_htfProps.Cp((m_T_salt_hot_target + T_salt_cold_in) / 2.0);	//[kJ/kg-K] Estimate the specific heat of the fluid in receiver
		double m_dot_salt_guess = std::numeric_limits<double>::quiet_NaN();
		if( I_bn > 1.E-6 )
		{
			double q_guess = 0.5*q_dot_inc_sum;		//[kW] Estimate the thermal power produced by the receiver				
			m_dot_salt_guess = q_guess / (c_guess*(m_T_salt_hot_target - T_salt_cold_in)*m_n_lines);	//[kg/s] Mass flow rate for each flow path
		}
		else	// The tower recirculates at night (based on earlier conditions)
		{
			// Enter recirculation mode, where inlet/outlet temps switch
			m_T_salt_hot_target = T_salt_cold_in;
			T_salt_cold_in = m_T_s_guess.at(0);		//T_s_guess is set to T_salt_hot before, so this just completes 
			m_dot_salt_guess = -3500.0 / (c_guess*(m_T_salt_hot_target - T_salt_cold_in) / 2.0);
		}
		T_salt_hot_guess = 9999.9;		//[K] Initial guess value for error calculation
		double err = -999.9;					//[-] Relative outlet temperature error
		double tol = std::numeric_limits<double>::quiet_NaN();
		if( m_night_recirc == 1 )
			tol = 0.0057;
		else
			tol = 0.0005;

		//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		//                            ITERATION STARTS HERE
		//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		int qq_max = 50;
		double m_dot_salt = std::numeric_limits<double>::quiet_NaN();
		int qq = 0;
		q_abs_sum = 0.0;

		while( fabs(err) > tol )
		{
			qq++;

			// if the problem fails to converge after 50 iterations, then the power is likely negligible and
			// ..the zero set can be returned
			if( qq > qq_max )
			{
				m_mode = C_csp_collector_receiver::OFF;  // Set the startup mode
				rec_is_off = true;
				break;
			}

			m_dot_salt = m_dot_salt_guess;

			for( int i = 0; i < m_n_panels; i++ )
			{
				m_T_s.at(i) = m_T_s_guess.at(i);
				m_T_panel_out.at(i) = m_T_panel_out_guess.at(i);
				m_T_panel_in.at(i) = m_T_panel_in_guess.at(i);
				// Now do the actual calculations
				m_T_panel_ave.at(i) = (m_T_panel_in.at(i) + m_T_panel_out.at(i)) / 2.0;		//[K] The average coolant temperature in each control volume
				//m_T_film.at(i,0) = (m_T_s.at(i,0) + m_T_panel_out.at(i,0))/2.0;					//[K] Film temperature
				m_T_film.at(i) = (m_T_s.at(i) + T_amb) / 2.0;					//[K] Film temperature
			}

			// Calculate the average surface temperature
			double T_s_sum = 0.0;
			for( int i = 0; i < m_n_panels; i++ )
				T_s_sum += m_T_s.at(i);
			double T_s_ave = T_s_sum / m_n_panels;
			double T_film_ave = (T_amb + m_T_salt_hot_target) / 2.0;

			// Convective coefficient for external forced convection using Siebers & Kraabel
			double k_film = ambient_air.cond(T_film_ave);				//[W/m-K] The conductivity of the ambient air
			double mu_film = ambient_air.visc(T_film_ave);			//[kg/m-s] Dynamic viscosity of the ambient air
			double rho_film = ambient_air.dens(T_film_ave, P_amb);	//[kg/m^3] Density of the ambient air
			double c_p_film = ambient_air.Cp(T_film_ave);				//[kJ/kg-K] Specific heat of the ambient air
			double Re_for = rho_film*v_wind*m_d_rec / mu_film;			//[-] Reynolds number
			double ksD = (m_od_tube / 2.0) / m_d_rec;						//[-] The effective roughness of the cylinder [Siebers, Kraabel 1984]
			double Nusselt_for = CSP::Nusselt_FC(ksD, Re_for);		//[-] S&K
			double h_for = Nusselt_for*k_film / m_d_rec*m_hl_ffact;		//[W/m^2-K] Forced convection heat transfer coefficient

			// Convection coefficient for external natural convection using Siebers & Kraabel
			// Note: This relationship applies when the surrounding properties are evaluated at ambient conditions [S&K]
			double beta = 1.0 / T_amb;												//[1/K] Volumetric expansion coefficient
			double nu_amb = ambient_air.visc(T_amb) / ambient_air.dens(T_amb, P_amb);	//[m^2/s] Kinematic viscosity		



			for( int i = 0; i < m_n_panels; i++ )
			{
				//for( int i = 0; i < m_n_panels/m_n_lines; i++ )
				//{
				// int i_fp = m_flow_pattern.at(j,i);
				int i_fp = i;
				// Natural convection
				double Gr_nat = fmax(0.0, CSP::grav*beta*(m_T_s.at(i_fp) - T_amb)*pow(m_h_rec, 3) / pow(nu_amb, 2));	//[-] Grashof Number at ambient conditions
				double Nusselt_nat = 0.098*pow(Gr_nat, (1.0 / 3.0))*pow(m_T_s.at(i_fp) / T_amb, -0.14);					//[-] Nusselt number
				double h_nat = Nusselt_nat*ambient_air.cond(T_amb) / m_h_rec*m_hl_ffact;							//[W/m^-K] Natural convection coefficient
				// Mixed convection
				double h_mixed = pow((pow(h_for, m_m_mixed) + pow(h_nat, m_m_mixed)), 1.0 / m_m_mixed)*4.0;			//(4.0) is a correction factor to match convection losses at Solar II (correspondance with G. Kolb, SNL)
				m_q_dot_conv.at(i_fp) = h_mixed*m_A_node*(m_T_s.at(i_fp) - m_T_film.at(i_fp));							//[W] Convection losses per node
				// Radiation from the receiver - Calculate the radiation node by node
				m_q_dot_rad.at(i_fp) = 0.5*CSP::sigma*m_epsilon*m_A_node*(2.0*pow(m_T_s.at(i_fp), 4) - pow(T_amb, 4) - pow(T_sky, 4))*m_hl_ffact;	//[W] Total radiation losses per node
				m_q_dot_loss.at(i_fp) = m_q_dot_rad.at(i_fp) + m_q_dot_conv.at(i_fp);			//[W] Total overall losses per node
				m_q_dot_abs.at(i_fp) = m_q_dot_inc.at(i_fp)*1000.0 - m_q_dot_loss.at(i_fp);	//[W] Absorbed flux at each node
				// Calculate the temperature drop across the receiver tube wall... assume a cylindrical thermal resistance
				double T_wall = (m_T_s.at(i_fp) + m_T_panel_ave.at(i_fp)) / 2.0;				//[K] The temperature at which the conductivity of the wall is evaluated
				double k_tube = tube_material.cond(T_wall);								//[W/m-K] The conductivity of the wall
				double R_tube_wall = m_th_tube / (k_tube*m_h_rec*m_d_rec*pow(CSP::pi, 2) / 2.0 / (double)m_n_panels);	//[K/W] The thermal resistance of the wall
				// Calculations for the inside of the tube						
				double mu_coolant = field_htfProps.visc(T_coolant_prop);					//[kg/m-s] Absolute viscosity of the coolant
				double k_coolant = field_htfProps.cond(T_coolant_prop);					//[W/m-K] Conductivity of the coolant
				rho_coolant = field_htfProps.dens(T_coolant_prop, 1.0);			//[kg/m^3] Density of the coolant

				u_coolant = m_dot_salt / (m_n_t*rho_coolant*pow((m_id_tube / 2.0), 2)*CSP::pi);	//[m/s] Average velocity of the coolant through the receiver tubes
				double Re_inner = rho_coolant*u_coolant*m_id_tube / mu_coolant;				//[-] Reynolds number of internal flow
				double Pr_inner = c_p_coolant*mu_coolant / k_coolant;							//[-] Prandtl number of internal flow
				double Nusselt_t;
				CSP::PipeFlow(Re_inner, Pr_inner, m_LoverD, m_RelRough, Nusselt_t, f);
				if( Nusselt_t <= 0.0 )
				{
					m_mode = C_csp_collector_receiver::OFF;		// Set the startup mode
					rec_is_off = true;
					break;
				}
				double h_inner = Nusselt_t*k_coolant / m_id_tube;								//[W/m^2-K] Convective coefficient between the inner tube wall and the coolant
				double R_conv_inner = 1.0 / (h_inner*CSP::pi*m_id_tube / 2.0*m_h_rec*m_n_t);	//[K/W] Thermal resistance associated with this value

				// Set up numerical flow grid
				//if( i == 0 )
				//	m_T_panel_in_guess.at(i_fp,0) = T_salt_cold_in;
				//else
				//	m_T_panel_in_guess.at(i_fp,0) = m_T_panel_out_guess.at(m_flow_pattern.at(j,i-1),0);

				// Set up numerical flow grid

				// Using flow pattern for direct steam receiver, which calls panels in flow order
				// The follow code reverts back to molten salt receiver convention, which calls panels in panel number order

				int j = -1;
				int i_comp = -1;
				bool found_loc = false;
				for( j = 0; j < 2; j++ )
				{
					for( int abc = 0; abc < m_n_panels / m_n_lines && !found_loc; abc++ )
					{
						if( m_flow_pattern.at(j, abc) == i )
							found_loc = true;
						i_comp = abc - 1;
					}
					if( found_loc )
						break;
				}
				if( i_comp == -1 )
					m_T_panel_in_guess.at(i_fp) = T_salt_cold_in;
				else
					m_T_panel_in_guess.at(i_fp) = m_T_panel_out.at(m_flow_pattern.at(j, i_comp));


				m_T_panel_out_guess.at(i_fp) = m_T_panel_in_guess.at(i_fp) + m_q_dot_abs.at(i_fp) / (m_dot_salt*c_p_coolant);	//[K] Energy balance for each node																																																
				m_T_panel_ave_guess.at(i_fp) = (m_T_panel_out_guess.at(i_fp) + m_T_panel_in_guess.at(i_fp)) / 2.0;				//[K] Panel average temperature
				m_T_s_guess.at(i_fp) = m_T_panel_ave_guess.at(i_fp) + m_q_dot_abs.at(i_fp)*(R_conv_inner + R_tube_wall);			//[K] Surface temperature based on the absorbed heat

				if( m_T_s_guess.at(i_fp) < 1.0 )
				{
					m_mode = C_csp_collector_receiver::OFF;  // Set the startup mode
					rec_is_off = true;
				}

				//}	// End of panels in flow path
				//if( rec_is_off )
				//	break;
			}	// End flow paths in receiver

			if( rec_is_off )
				break;

			q_conv_sum = 0.0; q_rad_sum = 0.0; //q_inc_sum = 0.0;
			q_abs_sum = 0.0;
			for( int i = 0; i < m_n_panels; i++ )
			{
				q_conv_sum += m_q_dot_conv.at(i);
				double blah = m_q_dot_conv.at(i);
				q_rad_sum += m_q_dot_rad.at(i);
				//q_inc_sum += m_q_dot_inc.at(i,0);
				q_abs_sum += m_q_dot_abs.at(i);
			}

			double T_salt_hot_guess_sum = 0.0;
			for( int j = 0; j < m_n_lines; j++ )
				T_salt_hot_guess_sum += m_T_panel_out_guess.at(m_flow_pattern.at(j, m_n_panels / m_n_lines - 1));		//[K] Update the calculated hot salt outlet temp
			T_salt_hot_guess = T_salt_hot_guess_sum / (double)m_n_lines;

			T_salt_hot_rec = 0.0;
			for (int j = 0; j < m_n_lines; j++)
				T_salt_hot_rec = fmax(T_salt_hot_rec, m_T_panel_out_guess.at(m_flow_pattern.at(j, m_n_panels / m_n_lines - 1)));

			// 8.10.2015 twn: Calculate outlet temperature after piping losses
			//if( m_Q_dot_piping_loss > 0.0 )
			//{
			//	double m_dot_salt_tot_temp = m_dot_salt*m_n_lines;		//[kg/s]
			//	double delta_T_piping = m_Q_dot_piping_loss / (m_dot_salt_tot_temp*c_p_coolant);	//[K]
			//	T_salt_hot_guess = T_salt_hot_guess - m_Q_dot_piping_loss/(m_dot_salt_tot_temp*c_p_coolant);	//[K]
			//}

			// 12.2016 : Updated SS piping losses based on specified overall heat transfer coefficient 
			m_Q_dot_piping_loss = 0.0;
			if (m_piping_loss_coeff > 0.0)
			{
				double m_dot_salt_tot_temp = m_dot_salt*m_n_lines;		// Total salt flow rate[kg/s]
				double riser_loss = 2.0*CSP::pi * (T_salt_cold_in - T_amb) / m_Rtot_riser; //[W/m]
				double downc_loss = 2.0*CSP::pi * (T_salt_hot_guess - T_amb) / m_Rtot_downc; //[W/m]
				m_Q_dot_piping_loss = 0.5*(riser_loss + downc_loss) * (m_h_tower*m_pipe_length_mult + m_pipe_length_add); // Total piping thermal loss [W]
				T_salt_hot_guess = T_salt_hot_guess - m_Q_dot_piping_loss / (m_dot_salt_tot_temp*c_p_coolant);			// Updated salt exit temperature after piping losses [K]
			}

			// 8.12.2015 twn: not using eta_therm in iteration loop - so move this calculation after loop
			//if( q_dot_inc_sum > 0.0 )
			//	eta_therm = q_abs_sum / (q_dot_inc_sum*1000.0);
			//else
			//	eta_therm = 0.0;

			err = (T_salt_hot_guess - m_T_salt_hot_target) / m_T_salt_hot_target;

			if( fabs(err) > tol )
			{
				m_dot_salt_guess = (q_abs_sum - m_Q_dot_piping_loss) / (m_n_lines*c_p_coolant*(m_T_salt_hot_target - T_salt_cold_in));			//[kg/s]

				if( m_dot_salt_guess < 1.E-5 )
				{
					m_mode = C_csp_collector_receiver::OFF;				//[-] Set the startup mode
					rec_is_off = true;
				}
			}
		}

		if( rec_is_off )
			break;

		// Now we can calculate some of the parasitics associated with pumping the coolant fluid
		// Calculating the pressure drop across the receiver panels
		m_dot_salt_tot = m_dot_salt*m_n_lines;
		double m_dot_tube = m_dot_salt / (double)m_n_t;		//[kg/s] The mass flow through each individual tube

		// Limit the HTF mass flow rate to the maximum, if needed
		if( (m_dot_salt_tot > m_dot_htf_max) || m_itermode == 2 )
		{
			err_od = (m_dot_salt_tot - m_dot_htf_max) / m_dot_htf_max;
			if( err_od < m_tol_od )
			{
				m_itermode = 1;
				m_od_control = 1.0;
				rec_is_defocusing = false;
			}
			else
			{
				m_od_control = m_od_control*pow((m_dot_htf_max / m_dot_salt_tot), 0.8);	//[-] Adjust the over-design defocus control by modifying the current value
				m_itermode = 2;
				rec_is_defocusing = true;
				// GOTO 15
			}
		}
	} while( rec_is_defocusing );

	// 8.12.2015 twn: not using eta_therm in iteration loop - so move this calculation after loop
	if( q_dot_inc_sum > 0.0 )
		eta_therm = q_abs_sum / (q_dot_inc_sum*1000.0);
	else
		eta_therm = 0.0;

	double DELTAP, Pres_D, W_dot_pump, q_thermal, q_startup;
	DELTAP = Pres_D = W_dot_pump = q_thermal = q_startup = std::numeric_limits<double>::quiet_NaN();

	// Adjust receiver state if SS mass flow calculation did not converge, but incident flux is sufficient to begin startup
	if (m_is_startup_transient)
	{
		if (m_mode_prev == C_csp_collector_receiver::OFF || m_mode_prev == C_csp_collector_receiver::STARTUP)	// Receiver was either off or starting up in previous time step
		{
			if (rec_is_off && q_dot_inc_sum >= total_req_preheat && q_dot_inc_min_panel >= panel_req_preheat)	// Total absorbed solar flux and minimum panel absorbed solar flux are sufficient to begin preheating
			{
				rec_is_off = false;
				startup_low_flux = true;
			}
		}
	}

	// Calculate solution parameters needed for transient model
	if (!rec_is_off && (m_is_transient || m_is_startup_transient))
	{
		trans_inputs.inlet_temp = T_salt_cold_in;
		param_inputs.mflow_tot = m_dot_salt_tot;
		param_inputs.c_htf = field_htfProps.Cp(T_coolant_prop)*1000.0;		// HTF specific heat at average temperature [J/kg-K] 
		param_inputs.rho_htf = field_htfProps.dens(T_coolant_prop, 1.0);	// HTF density at average temperature [kg/m3]
		param_inputs.mu_htf = field_htfProps.visc(T_coolant_prop);			// HTF viscosity at average temperature [kg/m/s]
		param_inputs.k_htf = field_htfProps.cond(T_coolant_prop);			// HTF conductivity at average temperature [W/m/K]
		param_inputs.Pr_htf = param_inputs.c_htf*param_inputs.mu_htf / param_inputs.k_htf;
		param_inputs.T_amb = T_amb;
		param_inputs.T_sky = T_sky;

		// Set panel incident solar energy and fill in initial guesses for property evaluation temperatures with steady state values
		param_inputs.qinc.fill(0.0);				// Solar energy incident on one tube (W)
		for (int i = 0; i < m_n_lines; i++)
		{
			param_inputs.Tfeval.at(0, i) = T_salt_cold_in;	  //Riser
			param_inputs.Tseval.at(0, i) = T_salt_cold_in;		
			param_inputs.Tfeval.at(m_n_elem - 1, i) = T_salt_hot_guess;	  //Downcomer
			param_inputs.Tseval.at(m_n_elem - 1, i) = T_salt_hot_guess;  
			for (int j = 1; j < m_n_elem - 1; j++)
			{
				if (m_flowelem_type.at(j, i) >= 0)		// Receiver panel
				{
					param_inputs.qinc.at(j, i) = m_q_dot_inc.at(m_flowelem_type.at(j, i))*1000. / double(m_n_t);
					param_inputs.Tfeval.at(j, i) = m_T_panel_ave_guess.at(m_flowelem_type.at(j, i));
					param_inputs.Tseval.at(j, i) = m_T_s_guess.at(m_flowelem_type.at(j, i));
				}
				if (m_flowelem_type.at(j, i) == -3)		// Crossover header
				{
					param_inputs.Tfeval.at(j, i) = param_inputs.Tfeval.at(j - 1, i); 
					param_inputs.Tseval.at(j, i) = param_inputs.Tfeval.at(j, i);	  
				}
			}
		}
	}

	double q_heat_trace_energy = 0.0;	//[J]
	double q_startup_energy = 0.0;		//[J]

	q_startup = 0.0;

	double time_required_su = step/3600.0;

	if( !rec_is_off )
	{
		m_dot_salt_tot_ss = m_dot_salt_tot;
		double m_dot_rec_des = m_q_rec_des / (c_p_coolant*(m_T_htf_hot_des - m_T_htf_cold_des)); // Design point receiver mass flow rate (kg/s)

		switch( input_operation_mode )
		{
		case C_csp_collector_receiver::STARTUP:

			// Startup model based on fixed time and energy requirements
			if (!m_is_startup_transient)
			{
				double time_require_su_energy = m_E_su_prev / (m_dot_salt_tot*c_p_coolant*(T_salt_hot_guess - T_salt_cold_in));	//[hr]
				double time_require_su_ramping = m_t_su_prev;

				double time_required_max = fmax(time_require_su_energy, time_require_su_ramping);	//[hr]

				double time_step_hrs = step / 3600.0;		//[hr]

				if( time_required_max  > time_step_hrs )		// Can't completely startup receiver in maximum allowable timestep
				{											// Need to advance timestep and try again
					time_required_su = time_step_hrs;		
					m_mode = C_csp_collector_receiver::STARTUP;
					q_startup = m_dot_salt_tot*c_p_coolant*(T_salt_hot_guess - T_salt_cold_in)*step / 3600.0;
				}
				else
				{
					time_required_su = time_required_max;		//[hr]
					m_mode = C_csp_collector_receiver::ON;

					double q_startup_energy_req = m_E_su_prev;	//[W-hr]
					double q_startup_ramping_req = m_dot_salt_tot*c_p_coolant*(T_salt_hot_guess - T_salt_cold_in)*m_t_su;	//[W-hr]
					q_startup = fmax(q_startup_energy_req, q_startup_ramping_req);
				}

				m_E_su = fmax(0.0, m_E_su_prev - m_dot_salt_tot*c_p_coolant*(T_salt_hot_guess - T_salt_cold_in)*step / 3600.0);
				m_t_su = fmax(0.0, m_t_su_prev - step / 3600.0);

				rec_is_off = true;
				calc_pump_performance(rho_coolant, m_dot_salt_tot, f, Pres_D, W_dot_pump);
				if (m_is_transient && m_mode == C_csp_collector_receiver::ON)		// Define temperature profile after startup if transient receiver model will be solved
				{
					param_inputs.tm = m_tm;	// Select combined fluid/solid thermal mass values
					param_inputs.mflow_tot = m_dot_salt_tot;
					update_pde_parameters(weather, false, param_inputs, trans_inputs);
					calc_ss_profile(trans_inputs, trans_outputs.t_profile, trans_outputs.t_profile_wall);
				}
			}


			// Startup model based on transient response of receiver temperature
			if (m_is_startup_transient)
			{
				double time_remaining = step;			// Remaining time in current time step [s]
				double time_heattrace = 0.0;
				double time_preheat = 0.0;
				double time_circulate = 0.0;
				double time_hold = 0.0;
				double min_circulate_time = 0.0;

				if (q_dot_inc_sum >= total_req_preheat && q_dot_inc_min_panel >= panel_req_preheat) // Available flux is sufficient for preheating	
				{
					double heat_trace_target = m_T_htf_cold_des;	// Target riser/downcomer temperature at end of heat_trace startup stage [K]
					double preheat_target = m_preheat_target;		// Target tube temperature at end of preheat startup stage [K]
					double circulation_target = m_startup_target;	// Target HTF outlet temperature at end of circulation startup stage [K]
					double m_dot_salt_startup = 0.0;				// Mass flow rate during startup 
					double Tmin_rec, Tmin_piping;
					Tmin_rec = Tmin_piping = std::numeric_limits<double>::quiet_NaN();

					m_mode = C_csp_collector_receiver::STARTUP;

					if (m_startup_mode_initial == -1)			// Startup didn't begin in a previous time step
					{
						m_startup_mode = HEAT_TRACE;
						m_total_startup_time_initial = 0.0;
						m_n_call_circ_initial = -1;
						m_minimum_startup_time = m_rec_su_delay*3600.0;
						if (!m_is_startup_from_solved_profile)   // Start from ambient temperature
						{
							trans_inputs.tinit.fill(T_amb);
							trans_inputs.tinit_wall.fill(T_amb);
						}
					}
					else
						m_startup_mode = m_startup_mode_initial;

					// Calculate current minimum receiver and piping temperatrues
					Tmin_rec = 5000.0;
					Tmin_piping = 5000.0;
					for (int i = 0; i < m_n_lines; i++)
					{
						for (int j = 0; j < m_n_elem; j++)
						{
							int p1 = trans_inputs.startpt.at(j);
							double Twall_min = fmin(trans_inputs.tinit.at(p1, i), trans_inputs.tinit.at(p1 + trans_inputs.nz.at(j)-1, i));
							if (m_flowelem_type.at(j, i) >= 0)  //Receiver
								Tmin_rec = fmin(Tmin_rec, Twall_min);
							if (m_flowelem_type.at(j, i) == -1 || m_flowelem_type.at(j, i) == -2) // Riser or downcomer
								Tmin_piping = fmin(Tmin_piping, Twall_min);
						}
					}

					if (m_startup_mode_initial == -1 && !m_is_enforce_min_startup && Tmin_rec > preheat_target)
						m_minimum_startup_time = 0.0;  // Minimum time not enforced for this start when receiver begins above preheat temperature

					m_total_startup_time = m_total_startup_time_initial;	// Total startup time completed in previous time steps
					m_n_call_circ = m_n_call_circ_initial;
					util::matrix_t<double> tinit_start = trans_inputs.tinit;    // Initial temperature profile at the start of the overall time step [K]	
					util::matrix_t<double> tinit_wall_start = trans_inputs.tinit_wall;
					util::matrix_t<double> q_inc_panel_full = param_inputs.qinc;  // Absorbed solar energy on panel (W) during operation

					while (time_remaining > 0.1 && m_mode == C_csp_collector_receiver::STARTUP)		// Receiver is starting up and there is time remaining in the current time step
					{
						trans_inputs.lam1.fill(0.0);  trans_inputs.lam2.fill(0.0);  trans_inputs.cval.fill(0.0);  // Reinitialize PDE solution parameters

						switch (m_startup_mode)
						{
						case HEAT_TRACE:
						{
							if (Tmin_piping > heat_trace_target)  // Riser and downcomer already above heat trace target temperature
								m_startup_mode = PREHEAT;
							else
							{
								param_inputs.qinc.fill(0.0);
								param_inputs.tm = m_tm_solid;
								param_inputs.mflow_tot = 0.0;
								solve_transient_startup_model(weather, param_inputs, trans_inputs, HEAT_TRACE, heat_trace_target, 0.0, time_remaining, trans_outputs, time_heattrace, q_heat_trace_energy);
								m_total_startup_time += time_heattrace;		
								time_remaining -= time_heattrace;					
								m_startup_mode = HEAT_TRACE;
								if (time_remaining > 0)						// Heat tracing startup stage is completed before the end of the time step --> move to preheat stage
								{
									m_startup_mode = PREHEAT;
									trans_inputs.tinit = trans_outputs.t_profile;
									trans_inputs.tinit_wall = trans_outputs.t_profile_wall;
									param_inputs.qinc = q_inc_panel_full;		// Update to full flux profile
								}
							}
						}
						break;

						case PREHEAT:
						{
							if (Tmin_rec > preheat_target)  // Entire receiver already above preheat target temperature
								m_startup_mode = CIRCULATE;
							else
							{
								param_inputs.mflow_tot = 0.0;
								param_inputs.tm = m_tm_solid;
								param_inputs.qinc.fill(m_tube_flux_startup*1000. * m_od_tube * m_h_rec); // Absorbed solar energy on tube (W) for preheat stage
								double preheat_energy = std::numeric_limits<double>::quiet_NaN();
								solve_transient_startup_model(weather, param_inputs, trans_inputs, PREHEAT, preheat_target, 0.0, time_remaining, trans_outputs, time_preheat, preheat_energy);
								q_startup_energy += preheat_energy;
								m_total_startup_time += time_preheat;									
								time_remaining -= time_preheat;		
								m_startup_mode = PREHEAT;
								if (time_remaining > 0)			// Preheating stage is finished before the end of the time step --> move to circulation stage
								{
									m_startup_mode = CIRCULATE;
									trans_inputs.tinit = trans_outputs.t_profile;
									trans_inputs.tinit_wall = trans_outputs.t_profile_wall;
								}
							}
						}
						break;

						case CIRCULATE:
						{
							m_n_call_circ++;

							// Update initial temperature profile after preheating
							if (m_n_call_circ == 0) // First time during the current startup that the fluid can circulate --> "tinit" still contains solid temperature profile, intial fluid temperature = cold inlet temperature
							{
								for (int j = 0; j < m_n_elem; j++)
								{
									double tinit_avg = (m_tm_solid.at(j) / m_tm.at(j)) * trans_inputs.tinit.at(trans_inputs.startpt.at(j), 0) + (1.0 - m_tm_solid.at(j) / m_tm.at(j))* T_salt_cold_in;	// Mass-weighted average of solid and fluid temperatures in element j
									for (int i = 0; i < m_n_lines; i++)
									{
										for (int k = 0; k < trans_inputs.nz.at(j); k++)
											trans_inputs.tinit.at(trans_inputs.startpt.at(j) + k, i) = tinit_avg;
									}
								}
							}
							trans_inputs.tinit_wall = trans_inputs.tinit;
							m_dot_salt_startup = fmax(m_dot_salt_tot, m_f_rec_min *m_dot_rec_des);	// HTF mass flow rate during startup (kg/s)	
							param_inputs.mflow_tot = m_dot_salt_startup;
							param_inputs.tm = m_tm;
							param_inputs.qinc = q_inc_panel_full;		// Update to full flux profile

							double circulate_energy = std::numeric_limits<double>::quiet_NaN();
							solve_transient_startup_model(weather, param_inputs, trans_inputs, CIRCULATE, circulation_target, min_circulate_time, time_remaining, trans_outputs, time_circulate, circulate_energy);
							m_total_startup_time += time_circulate;
							q_startup_energy += circulate_energy;
							time_remaining -= time_circulate;
							if (time_remaining <= 0.1)			// Target outlet temperature not achieved within the current time step
								m_startup_mode = CIRCULATE;
							else
							{
								if (m_total_startup_time < m_minimum_startup_time)		// Receiver has reached temperature target, but minimum startup time requirement has not been met
								{
									m_startup_mode = HOLD;
									trans_inputs.tinit = trans_outputs.t_profile;
									trans_inputs.tinit_wall = trans_outputs.t_profile_wall;
								}
								else			// Receiver is finished starting up and the minimum startup time requirement has been met
								{
									m_mode = C_csp_collector_receiver::ON;
									m_startup_mode = -1;
								}
							}
						}
						break;

						case HOLD:
						{
							double required_hold_time = m_minimum_startup_time - m_total_startup_time;	// Time remaining (s) to satisfy the minimum required startup time
							time_hold = fmin(required_hold_time, time_remaining);
							param_inputs.tm = m_tm;		
							
							m_dot_salt_startup = fmax(m_dot_salt_tot, m_f_rec_min*m_dot_rec_des);
							param_inputs.mflow_tot = m_dot_salt_startup;
							if (time_hold > time_remaining)		// Startup time requirement will not be fulfilled in the current time step
							{
								solve_transient_model(weather, time_hold, 150.0, param_inputs, trans_inputs, trans_outputs);	// Continue circulating fluid through receiver during hold time
								q_startup_energy = q_startup_energy + trans_outputs.timeavg_qnet* time_hold;					// Energy [J] used for startup during the time step	
								m_total_startup_time = m_total_startup_time + time_hold;
								time_remaining = time_remaining - time_hold;	// Remaining time in current timestep
								m_startup_mode = HOLD;
							}
							else  // Startup time requirement will be fulfilled in the current time step --> call in "circulate" mode to ensure that temperature requirement will also be met
							{
								m_startup_mode = CIRCULATE;
								min_circulate_time = time_hold;
							}
						}
						break;
						}
					}

					q_startup = q_startup_energy / 3600.0;					// Startup energy (W-hr) --> Doesn't include heat trace energy
					time_required_su = (step - time_remaining) / 3600.0;	// Total amount of time in current time step needed for startup [hr]
					trans_inputs.tinit = tinit_start;						// Revert back to initial temperature profile at the start of the full time step
					trans_inputs.tinit_wall = tinit_wall_start;
					m_dot_salt_tot = m_dot_salt_startup;					// Mass flow rate (kg/s)
					W_dot_pump = 0.0;
					if (time_circulate + time_hold > 0)						// HTF is flowing for at least part of the startup time
					{
						// Re-calculate pressure drop based on flow rate during startup
						double mu_coolant = field_htfProps.visc(T_coolant_prop);		//[kg/m-s] Absolute viscosity of the coolant
						double k_coolant = field_htfProps.cond(T_coolant_prop);			//[W/m-K] Conductivity of the coolant
						rho_coolant = field_htfProps.dens(T_coolant_prop, 1.0);			//[kg/m^3] Density of the coolant
						double fstartup, Nusselt_t;
						u_coolant = m_dot_salt_tot / (m_n_t*rho_coolant*pow((m_id_tube / 2.0), 2)*CSP::pi);	//[m/s] Average velocity of the coolant through the receiver tubes
						double Re_inner = rho_coolant*u_coolant*m_id_tube / mu_coolant;				//[-] Reynolds number of internal flow
						double Pr_inner = c_p_coolant*mu_coolant / k_coolant;						//[-] Prandtl number of internal flow
						CSP::PipeFlow(Re_inner, Pr_inner, m_LoverD, m_RelRough, Nusselt_t, fstartup);
						calc_pump_performance(rho_coolant, m_dot_salt_tot, fstartup, Pres_D, W_dot_pump);
						W_dot_pump = W_dot_pump*(time_circulate + time_hold) / (time_required_su*3600.0);	 // Average pump work over the startup time
					}

				}
				else			// Not enough power available to begin (or continue) startup
				{
					q_startup = 0.0;
					m_mode = C_csp_collector_receiver::OFF;
				}
				rec_is_off = true;
			}

			break;

		case C_csp_collector_receiver::ON:

			// Steady state receiver model
			if (!m_is_transient)
			{
				if (m_E_su_prev > 0.0 || m_t_su_prev > 0.0)
				{
					m_E_su = fmax(0.0, m_E_su_prev - m_dot_salt_tot*c_p_coolant*(T_salt_hot_guess - T_salt_cold_in)*step / 3600.0);	//[W-hr]
					m_t_su = fmax(0.0, m_t_su_prev - step / 3600.0);	//[hr]

					if (m_E_su + m_t_su > 0.0)
					{
						m_mode = C_csp_collector_receiver::STARTUP;		// If either are greater than 0, we're staring up but not finished

						// 4.28.15 twn: Startup energy also needs to consider energy consumed during time requirement, if that is greater than energy requirement
						//q_startup = (m_E_su_prev - m_E_su) / (step / 3600.0)*1.E-6;
						q_startup = m_dot_salt_tot*c_p_coolant*(T_salt_hot_guess - T_salt_cold_in)*step / 3600.0;
						rec_is_off = true;
						f_rec_timestep = 0.0;
					}
					else
					{
						m_mode = C_csp_collector_receiver::ON;

						double q_startup_energy_req = m_E_su_prev;	//[W-hr]
						double q_startup_ramping_req = m_dot_salt_tot*c_p_coolant*(T_salt_hot_guess - T_salt_cold_in)*m_t_su;	//[W-hr]
						q_startup = fmax(q_startup_energy_req, q_startup_ramping_req);

						// Adjust the available mass flow to reflect startup
						m_dot_salt_tot = fmin((1.0 - m_t_su_prev / (step / 3600.0))*m_dot_salt_tot, m_dot_salt_tot - m_E_su_prev / ((step / 3600.0)*c_p_coolant*(T_salt_hot_guess - T_salt_cold_in)));
						f_rec_timestep = fmax(0.0, fmin(1.0 - m_t_su_prev / (step / 3600.0), 1.0 - m_E_su_prev / (m_dot_salt_tot*c_p_coolant*(T_salt_hot_guess - T_salt_cold_in))));
					}
					//4.28.15 twn: Startup energy needs to consider
					//q_startup = (m_E_su_prev - m_E_su) / (step / 3600.0)*1.E-6;
				}
				else
				{
					m_E_su = m_E_su_prev;
					m_t_su = m_t_su_prev;
					m_mode = C_csp_collector_receiver::ON;
					q_startup = 0.0;

					if (q_dot_inc_sum*1.E3 < m_q_dot_inc_min)
					{
						// If output here is less than specified allowed minimum, then need to shut off receiver
						m_mode = C_csp_collector_receiver::OFF;

						// Include here outputs that are ONLY set to zero if receiver completely off, and not attempting to start-up
						W_dot_pump = 0.0;
						// Pressure drops
						DELTAP = 0.0; Pres_D = 0.0; u_coolant = 0.0;
					}
				}
				q_thermal = m_dot_salt_tot*c_p_coolant*(T_salt_hot_guess - T_salt_cold_in);
				q_thermal_ss = m_dot_salt_tot_ss*c_p_coolant*(T_salt_hot_guess - T_salt_cold_in);
				calc_pump_performance(rho_coolant, m_dot_salt_tot, f, Pres_D, W_dot_pump);

				if (m_mode == C_csp_collector_receiver::ON && m_is_startup_from_solved_profile)  // Calculate temperature profile
				{
					param_inputs.tm = m_tm;	
					param_inputs.mflow_tot = m_dot_salt_tot;
					update_pde_parameters(weather, false, param_inputs, trans_inputs);
					calc_ss_profile(trans_inputs, trans_outputs.t_profile, trans_outputs.t_profile_wall);
				}

			}

			// Transient receiver model
			if (m_is_transient)
			{
				q_startup = 0.0;
				m_mode = C_csp_collector_receiver::ON;
				q_thermal = m_dot_salt_tot*c_p_coolant*(T_salt_hot_guess - T_salt_cold_in);			// Steady state thermal power (W)
				q_thermal_ss = m_dot_salt_tot_ss*c_p_coolant*(T_salt_hot_guess - T_salt_cold_in);
				calc_pump_performance(rho_coolant, m_dot_salt_tot, f, Pres_D, W_dot_pump);

				if (q_dot_inc_sum*1.E3 < m_q_dot_inc_min)				// Receiver is not allowed to operate
				{
					m_mode = C_csp_collector_receiver::OFF;
					W_dot_pump = 0.0;
					DELTAP = 0.0; Pres_D = 0.0; u_coolant = 0.0;
				}
				else
				{
					param_inputs.tm = m_tm;	// Set thermal mass values with both fluid and solid
					param_inputs.mflow_tot = m_dot_salt_tot;
					solve_transient_model(weather, step, 100.0, param_inputs, trans_inputs, trans_outputs);
					trans_outputs.timeavg_eta_therm = 1.0 - (trans_outputs.timeavg_conv_loss + trans_outputs.timeavg_rad_loss) / (q_dot_inc_sum * 1000.);	//[-] Time-averaged recevier thermal efficiency during the time step
				}
			}

			if (q_dot_inc_sum*1.E3 < m_q_dot_inc_min)
				rec_is_off = true;

			break;

		case C_csp_collector_receiver::STEADY_STATE:

			m_mode = C_csp_collector_receiver::STEADY_STATE;
			f_rec_timestep = 1.0;
			calc_pump_performance(rho_coolant, m_dot_salt_tot, f, Pres_D, W_dot_pump);
			q_thermal = m_dot_salt_tot*c_p_coolant*(T_salt_hot_guess - T_salt_cold_in);
			q_thermal_ss = m_dot_salt_tot_ss*c_p_coolant*(T_salt_hot_guess - T_salt_cold_in);

			if (m_is_startup_transient && startup_low_flux)    // Incident flux is high enough for startup but not for steady state operation. Report nonzero q_thermal to allow startup
				q_thermal = q_dot_inc_sum*1000.0;
			else
			{
				if (q_dot_inc_sum*1.E3 < m_q_dot_inc_min && m_mode_prev == C_csp_collector_receiver::ON)
					rec_is_off = true;
			}

			break;
		
		}	// End switch() on input_operation_mode

	}
	else
	{	// If receiver was off BEFORE startup deductions
		m_mode = C_csp_collector_receiver::OFF;

		// Include here outputs that are ONLY set to zero if receiver completely off, and not attempting to start-up
		W_dot_pump = 0.0;
		// Pressure drops
		DELTAP = 0.0; Pres_D = 0.0; u_coolant = 0.0;

		m_startup_mode_initial = -1;
		m_startup_mode = -1;
	}

	if( rec_is_off )
	{
		// 900 continue	// Receiver isn't producing usable energy
		m_dot_salt_tot = 0.0; eta_therm = 0.0; /*W_dot_pump = 0.0;*/
		q_conv_sum = 0.0; q_rad_sum = 0.0; m_T_s.fill(0.0); q_thermal = 0.0;
		// Set the receiver outlet temperature equal to the inlet design temperature
		T_salt_hot_guess = m_T_htf_cold_des;
		T_salt_hot_rec = m_T_htf_cold_des;
		q_dot_inc_sum = 0.0;
		// Pressure drops
		/*DELTAP = 0.0; Pres_D = 0.0; u_coolant = 0.0;*/
		// Set receiver startup energy to 0
		// q_startup = 0.0;
		// ISCC outputs
		m_dot_salt_tot_ss = 0.0; f_rec_timestep = 0.0; q_thermal_ss = 0.0;

		// Reset m_od_control
		m_od_control = 1.0;		//[-]

		if (m_is_transient || m_is_startup_transient)
		{
			trans_outputs.timeavg_conv_loss = 0.0; trans_outputs.timeavg_rad_loss = 0.0; trans_outputs.timeavg_piping_loss = 0.0; trans_outputs.timeavg_qthermal = 0.0;
			trans_outputs.timeavg_tout = m_T_htf_cold_des;
			trans_outputs.tout = m_T_htf_cold_des;
			trans_outputs.max_tout = m_T_htf_cold_des;
			trans_outputs.min_tout = m_T_htf_cold_des;
			trans_outputs.max_rec_tout = m_T_htf_cold_des;
		}
	}

	// Steady state outputs
	ms_outputs.m_m_dot_salt_tot = m_dot_salt_tot*3600.0;		//[kg/hr] convert from kg/s
	ms_outputs.m_eta_therm = eta_therm;							//[-] RECEIVER thermal efficiency (includes radiation and convective losses. reflection losses are contained in receiver flux model)
	ms_outputs.m_W_dot_pump = W_dot_pump / 1.E6;				//[MW] convert from W
	ms_outputs.m_q_conv_sum = q_conv_sum / 1.E6;				//[MW] convert from W
	ms_outputs.m_q_rad_sum = q_rad_sum / 1.E6;					//[MW] convert from W
	ms_outputs.m_Q_thermal = q_thermal / 1.E6;					//[MW] convert from W
	ms_outputs.m_T_salt_hot = T_salt_hot_guess - 273.15;		//[C] convert from K
	ms_outputs.m_field_eff_adj = field_eff_adj;					//[-]
	ms_outputs.m_component_defocus = m_od_control;				//[-]
	ms_outputs.m_q_dot_rec_inc = q_dot_inc_sum / 1.E3;			//[MW] convert from kW
	ms_outputs.m_q_startup = q_startup/1.E6;					//[MW-hr] convert from W-hr
	ms_outputs.m_dP_receiver = DELTAP*m_n_panels / m_n_lines / 1.E5;	//[bar] receiver pressure drop, convert from Pa
	ms_outputs.m_dP_total = Pres_D*10.0;						//[bar] total pressure drop, convert from MPa
	ms_outputs.m_vel_htf = u_coolant;							//[m/s]
	ms_outputs.m_T_salt_cold = T_salt_cold_in - 273.15;			//[C] convert from K
	ms_outputs.m_m_dot_ss = m_dot_salt_tot_ss*3600.0;			//[kg/hr] convert from kg/s
	ms_outputs.m_q_dot_ss = q_thermal_ss / 1.E6;				//[MW] convert from W
	ms_outputs.m_f_timestep = f_rec_timestep;					//[-]
	ms_outputs.m_time_required_su = time_required_su*3600.0;	//[s], convert from hr in code

	ms_outputs.m_inst_T_salt_hot = T_salt_hot_guess - 273.15;		//[C] Instantaneous salt outlet T at the end of the time step
	ms_outputs.m_max_T_salt_hot = T_salt_hot_guess - 273.15;	//[C] Maximum salt outlet T during the time step
	ms_outputs.m_min_T_salt_hot = T_salt_hot_guess - 273.15;	//[C] Minimum salt outlet T during the time step
	ms_outputs.m_max_rec_tout = T_salt_hot_rec - 273.15;		//[C] Maximum salt T (receiver outlet) during the time step
	ms_outputs.m_q_heattrace = 0.0;								//[MWt-hr] Power required for heat tracing 

	if(q_thermal > 0.0)
		ms_outputs.m_q_dot_piping_loss = m_Q_dot_piping_loss/1.E6;	//[MWt]
	else
		ms_outputs.m_q_dot_piping_loss = 0.0;		//[MWt]


	// Transient model outputs
	if ((m_is_transient && input_operation_mode == C_csp_collector_receiver::ON) || (m_is_startup_transient && input_operation_mode == C_csp_collector_receiver::STARTUP))		// Transient model is solved
	{
		if (q_dot_inc_sum == 0.0)
			ms_outputs.m_eta_therm = 0.0;
		else
			ms_outputs.m_eta_therm = trans_outputs.timeavg_eta_therm;		//[-] Time-averaged recevier thermal efficiency during the time step

		ms_outputs.m_q_conv_sum = trans_outputs.timeavg_conv_loss / 1.e6;	//[MWt] Time-averaged receiver convective heat loss
		ms_outputs.m_q_rad_sum = trans_outputs.timeavg_rad_loss / 1.e6;		//[MWt] Time-averaged receiver radiative heat loss
		ms_outputs.m_Q_thermal = trans_outputs.timeavg_qthermal / 1.e6;		//[MWt] Time-averaged thermal power delivered to TES/PC
		ms_outputs.m_q_dot_piping_loss = trans_outputs.timeavg_piping_loss / 1.e6;			//[MWt] Time-averaged piping loss
		ms_outputs.m_q_heattrace = q_heat_trace_energy / 1.e6 / 3600.0;	//[MWt-hr] Power required for heat tracing during the time step
		ms_outputs.m_T_salt_hot = trans_outputs.timeavg_tout - 273.15;		//[C] Time-averaged downcomer outlet T during the time step
		ms_outputs.m_inst_T_salt_hot = trans_outputs.tout - 273.15;			//[C] Instantaneous salt outlet T at the end of the time step
		ms_outputs.m_max_T_salt_hot = trans_outputs.max_tout - 273.15;		//[C] Maximum salt outlet T during the time step
		ms_outputs.m_min_T_salt_hot = trans_outputs.min_tout - 273.15;		//[C] Minimum salt outlet T during the time step
		ms_outputs.m_max_rec_tout = trans_outputs.max_rec_tout - 273.15;		//[C] Maximum salt T (receiver outlet) during the time step
		ms_outputs.m_Twall_inlet = trans_outputs.tube_temp_inlet - 273.15;
		ms_outputs.m_Twall_outlet = trans_outputs.tube_temp_outlet - 273.15;
		ms_outputs.m_Triser = trans_outputs.t_profile.at(0, 0) - 273.15;
		ms_outputs.m_Tdownc = trans_outputs.t_profile.at(trans_inputs.startpt.at(m_n_elem-1), 0) - 273.15;

	}

	m_eta_field_iter_prev = field_eff;	//[-]
}

void C_mspt_receiver_222::off(const C_csp_weatherreader::S_outputs &weather,
	const C_csp_solver_htf_1state &htf_state_in,
	const C_csp_solver_sim_info &sim_info)
{
	// Don't currently need *any* of these inputs, but if we add recirculation or thermal capacitance it would be helpful to have in place
	m_mode = C_csp_collector_receiver::OFF;

	// Assuming no night recirculation, so... these should be zero
	ms_outputs.m_m_dot_salt_tot = 0.0;		//[kg/hr] convert from kg/s
	ms_outputs.m_eta_therm = 0.0;			//[-] RECEIVER thermal efficiency (includes radiation and convective losses. reflection losses are contained in receiver flux model)
	ms_outputs.m_W_dot_pump = 0.0;			//[MW] convert from W
	ms_outputs.m_q_conv_sum = 0.0;			//[MW] convert from W
	ms_outputs.m_q_rad_sum = 0.0;			//[MW] convert from W
	ms_outputs.m_Q_thermal = 0.0;			//[MW] convert from W
	ms_outputs.m_T_salt_hot = 0.0;			//[C] convert from K
	ms_outputs.m_field_eff_adj = 0.0;		//[-]
	ms_outputs.m_component_defocus = 1.0;	//[-]
	ms_outputs.m_q_dot_rec_inc = 0.0;		//[MW] convert from kW
	ms_outputs.m_q_startup = 0.0;			//[MW-hr] convert from W-hr
	ms_outputs.m_dP_receiver = 0.0;			//[bar] receiver pressure drop, convert from Pa
	ms_outputs.m_dP_total = 0.0;			//[bar] total pressure drop, convert from MPa
	ms_outputs.m_vel_htf = 0.0;				//[m/s]
	ms_outputs.m_T_salt_cold = 0.0;			//[C] convert from K
	ms_outputs.m_m_dot_ss = 0.0;			//[kg/hr] convert from kg/s
	ms_outputs.m_q_dot_ss = 0.0;			//[MW] convert from W
	ms_outputs.m_f_timestep = 0.0;			//[-]
	ms_outputs.m_time_required_su = sim_info.ms_ts.m_step;	//[s], convert from hr in code
	ms_outputs.m_q_dot_piping_loss = 0.0;	//[MWt]
	
	ms_outputs.m_inst_T_salt_hot = 0.0;
	ms_outputs.m_max_T_salt_hot = 0.0;
	ms_outputs.m_min_T_salt_hot = 0.0;
	ms_outputs.m_max_rec_tout = 0.0;
	ms_outputs.m_q_heattrace = 0.0;
	ms_outputs.m_Twall_inlet = 0.0;
	ms_outputs.m_Twall_outlet = 0.0;
	ms_outputs.m_Triser = 0.0;
	ms_outputs.m_Tdownc = 0.0;

	
	// Solve transient model for receiver wall temperatures
	if (m_is_startup_from_solved_profile)
	{
		double step = sim_info.ms_ts.m_step;
		double hour = sim_info.ms_ts.m_time / 3600.0;
		param_inputs.T_amb = weather.m_tdry + 273.15;
		param_inputs.T_sky = CSP::skytemp(weather.m_tdry + 273.15, weather.m_tdew + 273.15, hour);
		param_inputs.qinc.fill(0.0);
		param_inputs.tm = m_tm_solid;
		param_inputs.mflow_tot = 0.0;
		trans_inputs.tinit = trans_inputs.tinit_wall; // Set "fluid" temperature to wall temperature
		trans_inputs.inlet_temp = 0.0;
		solve_transient_model(weather,step, 50.0, param_inputs, trans_inputs, trans_outputs);
		ms_outputs.m_Twall_inlet = trans_outputs.tube_temp_inlet - 273.15;
		ms_outputs.m_Twall_outlet = trans_outputs.tube_temp_outlet - 273.15;
		ms_outputs.m_Triser = trans_outputs.t_profile.at(0, 0)-273.15;
		ms_outputs.m_Tdownc = trans_outputs.t_profile.at(trans_inputs.startpt.at(m_n_elem - 1), 0) - 273.15;

		// Overwrite solution for crossover header assuming same cooling rate as receiver
		for (int j = 0; j < m_n_elem; j++)	
		{
			if (m_flowelem_type.at(j, 0) == -3)  
			{
				for (int i = 0; i < m_n_lines; i++)	
				{
					trans_outputs.timeavg_temp.at(j, i) = trans_outputs.timeavg_temp.at(j-1, i);
					int krec = trans_inputs.startpt.at(j-1);
					for (int q = 0; q < trans_inputs.nz.at(j); q++)
					{
						int k = trans_inputs.startpt.at(j) + q;
						trans_outputs.t_profile.at(k, i) = trans_outputs.t_profile.at(krec, i);
						trans_outputs.t_profile_wall.at(k, i) = trans_outputs.t_profile.at(k, i);
					}
				}
			}
		}
		
	}

	return;
}

void C_mspt_receiver_222::converged()
{
	// Check HTF props?
	//!MJW 9.8.2010 :: Call the property range check subroutine with the inlet and outlet HTF temps to make sure they're in the valid range
	//call check_htf(Coolant,T_salt_hot)
	//call check_htf(Coolant,T_salt_cold)

	if( m_mode == C_csp_collector_receiver::STEADY_STATE )
	{
		throw(C_csp_exception("Receiver should only be run at STEADY STATE mode for estimating output. It must be run at a different mode before exiting a timestep",
			"MSPT receiver converged method"));
	}

	if( m_mode == C_csp_collector_receiver::OFF )
	{
		m_E_su = m_q_rec_des * m_rec_qf_delay;
		m_t_su = m_rec_su_delay;
	}

	m_mode_prev = m_mode;
	m_E_su_prev = m_E_su;
	m_t_su_prev = m_t_su;

	m_itermode = 1;
	m_od_control = 1.0;
	m_eta_field_iter_prev = 1.0;		//[-]

	m_ncall = -1;

	m_startup_mode_initial = m_startup_mode;
	m_n_call_circ_initial = m_n_call_circ;
	m_total_startup_time_initial = m_total_startup_time;
	trans_inputs.tinit = trans_outputs.t_profile;
	trans_inputs.tinit_wall = trans_outputs.t_profile_wall;
}

int C_mspt_receiver_222::get_operating_state()
{
	return m_mode_prev;
}

void C_mspt_receiver_222::clear_outputs()
{
	ms_outputs.m_m_dot_salt_tot = 
		ms_outputs.m_eta_therm = 
		ms_outputs.m_W_dot_pump = 
		ms_outputs.m_q_conv_sum = 
		ms_outputs.m_q_rad_sum = 
		ms_outputs.m_Q_thermal =
		ms_outputs.m_T_salt_hot = 
		ms_outputs.m_field_eff_adj = 
		ms_outputs.m_component_defocus =
		ms_outputs.m_q_dot_rec_inc = 
		ms_outputs.m_q_startup = 
		ms_outputs.m_dP_receiver = 
		ms_outputs.m_dP_total =
		ms_outputs.m_vel_htf = 
		ms_outputs.m_T_salt_cold = 
		ms_outputs.m_m_dot_ss = 
		ms_outputs.m_q_dot_ss = 
		ms_outputs.m_f_timestep = std::numeric_limits<double>::quiet_NaN();

	ms_outputs.m_max_T_salt_hot =
		ms_outputs.m_min_T_salt_hot =
		ms_outputs.m_max_rec_tout =
		ms_outputs.m_q_heattrace = std::numeric_limits<double>::quiet_NaN();

	ms_outputs.m_Twall_inlet = ms_outputs.m_Twall_outlet = std::numeric_limits<double>::quiet_NaN();
}

void C_mspt_receiver_222::calc_pump_performance(double rho_f, double mdot, double ffact, double &PresDrop_calc, double &WdotPump_calc)
{

    // Pressure drop calculations
	double u_coolant = mdot / (m_n_lines * m_n_t*rho_f* m_id_tube * m_id_tube * 0.25 * CSP::pi);	//[m/s] Average velocity of the coolant through the receiver tubes

	double L_e_45 = 16.0;						// The equivalent length produced by the 45 degree bends in the tubes - Into to Fluid Mechanics, Fox et al.
	double L_e_90 = 30.0;						// The equivalent length produced by the 90 degree bends in the tubes
	double DELTAP_tube = rho_f*(ffact*m_h_rec / m_id_tube*pow(u_coolant, 2) / 2.0);	//[Pa] Pressure drop across the tube, straight length
	double DELTAP_45 = rho_f*(ffact*L_e_45*pow(u_coolant, 2) / 2.0);					//[Pa] Pressure drop across 45 degree bends
	double DELTAP_90 = rho_f*(ffact*L_e_90*pow(u_coolant, 2) / 2.0);					//[Pa] Pressure drop across 90 degree bends
	double DELTAP = DELTAP_tube + 2 * DELTAP_45 + 4 * DELTAP_90;						//[Pa] Total pressure drop across the tube with (4) 90 degree bends, (2) 45 degree bends
	double DELTAP_h_tower = rho_f*m_h_tower*CSP::grav;						//[Pa] The pressure drop from pumping up to the receiver
	double DELTAP_net = DELTAP*m_n_panels / (double)m_n_lines + DELTAP_h_tower;		//[Pa] The new pressure drop across the receiver panels
	PresDrop_calc = DELTAP_net*1.E-6;			//[MPa]
	double est_load = fmax(0.25, mdot / m_m_dot_htf_des) * 100;		//[%] Relative pump load. Limit to 25%
	double eta_pump_adj = m_eta_pump*(-2.8825E-9*pow(est_load, 4) + 6.0231E-7*pow(est_load, 3) - 1.3867E-4*pow(est_load, 2) + 2.0683E-2*est_load);	//[-] Adjusted pump efficiency
	WdotPump_calc = DELTAP_net*mdot / rho_f / eta_pump_adj;

}

HTFProperties *C_mspt_receiver_222::get_htf_property_object()
{
    return &field_htfProps;
}

double C_mspt_receiver_222::calc_external_convection_coeff(const C_csp_weatherreader::S_outputs &weather, double Twall)
{
	double T_amb = weather.m_tdry + 273.15;
	double P_amb = weather.m_pres*100.0;
	double v_wind_10 = weather.m_wspd;
	double v_wind = log((m_h_tower + m_h_rec / 2) / 0.003) / log(10.0 / 0.003)*v_wind_10;
	double T_film_ave = 0.5*(T_amb + Twall);
	double Re_for = ambient_air.dens(T_film_ave, P_amb)*v_wind*m_d_rec / ambient_air.visc(T_film_ave);			//[-] Reynolds number for external forced convection
	double ksD = (m_od_tube / 2.0) / m_d_rec;									//[-] The effective roughness of the cylinder [Siebers, Kraabel 1984]
	double Nufor = CSP::Nusselt_FC(ksD, Re_for);								//[-] S&K
	double hfor = Nufor*ambient_air.cond(T_film_ave) / m_d_rec;					//[W/m^2-K] Forced convection heat transfer coefficient

	double nu_amb = ambient_air.visc(T_amb) / ambient_air.dens(T_amb, P_amb);						//[m^2/s] Kinematic viscosity of ambient air
	double Gr = fmax(0.0, CSP::grav*(Twall-T_amb)*pow(m_h_rec, 3) / pow(nu_amb, 2) / T_amb);		//[-] Grashof Number at ambient conditions
	double Nunat = 0.098*pow(Gr, (1.0 / 3.0))*pow(Twall / T_amb, -0.14);							// [-] Nusselt number
	double hnat = Nunat*ambient_air.cond(T_amb) / m_h_rec;									// [W/m^-K] Natural convection coefficient
	double hmix = pow((pow(hfor, m_m_mixed) + pow(hnat, m_m_mixed)), 1.0 / m_m_mixed)*4.0;	// (4.0) is a correction factor to match convection losses at Solar II (correspondance with G. Kolb, SNL)

	return hmix;
}

void C_mspt_receiver_222::calc_header_size(double pdrop, double mdot, double rhof, double muf, double Lh, double &id_calc, double &th_calc, double &od_calc)
{
	// Calculate minimum header size to meet pressure drop requirement
	double id_min, Re_h;
	double fh = 0.015;		// Initial guess for friction factor in header
	double Nucalc = 0.0;
	double id_min_prev = 0.0;
	for (int i = 0; i < 10; i++){
		id_min = pow(8.0*fh*mdot*mdot*Lh / rhof / pow(CSP::pi, 2) / pdrop, 0.2);		// Minimum Header ID [m] to meet pressure drop requirement
		Re_h = 4.0*mdot / CSP::pi / muf / id_min;										// Reynolds number for header
		CSP::PipeFlow(Re_h, 4.0, Lh / id_min, 4.5e-5 / id_min, Nucalc, fh);				// Update header friction factor
		if (fabs(id_calc - id_min_prev) <= 0.001)
			break;
		else
			id_min_prev = id_min;
	}

	// Find schedule 40 pipe size with ID >= calculated minimum header size 
	double wall, id;
	double odin[26] = { 0.405, 0.54, 0.675, 0.84, 1.05, 1.315, 1.66, 1.9, 2.375, 2.875, 3.5, 4.0, 4.5, 5.563, 6.625, 8.625, 10.75, 12.75, 14.0, 16.0, 18.0, 20.0, 24.0, 32.0, 34.0, 36.0 };		//Pipe OD [in]
	double wallin[26] = { 0.068, 0.088, 0.091, 0.109, 0.113, 0.133, 0.14, 0.145, 0.154, 0.203, 0.216, 0.226, 0.237, 0.258, 0.28, 0.322, 0.365, 0.406, 0.437, 0.5, 0.562, 0.593, 0.687, 0.688, 0.688, 0.75 }; //Schedule 40 pipe wall thickness [in]
	int i = 0;
	while (id_min / 0.0254 > odin[i] - 2 * wallin[i] && i <= 25){
		i++;
	}
	if (i <= 25){
		wall = wallin[i] * 0.0254; id = odin[i] * 0.0254 - 2 * wall;
	}
	else{
		id = id_min; wall = wallin[25] * 0.0254;
	}
	id_calc = id;
	th_calc = wall;
	od_calc = id + 2 * wall;
}

double C_mspt_receiver_222::interpolate(double x, const vector<double> &xarray, const vector<double> &yarray, int klow, int khigh)
{
	// Linear interpolation between discrete tabulated points
	// x = value of independent variable
	// xarray = independent variable points (assumed to be increasing between klow and khigh), 
	// yarray = dependent variable points
	// klow, khigh = lowest,highest indicies of interest 

	int jl = klow, ju = khigh;
	int jm;
	while (ju - jl > 1)
	{
		jm = (ju + jl) / 2;	//middle index of the range
		if (x < xarray.at(jm)) ju = jm;
		else jl = jm;
	}
	double yinterp = yarray.at(jl) + (yarray.at(ju) - yarray.at(jl)) / (xarray.at(ju) - xarray.at(jl)) * (x - xarray.at(jl));
	return yinterp;
}

double C_mspt_receiver_222::integrate(double xlow, double xhigh, const vector<double> &xarray, const vector<double> &yarray, int klow, int khigh)
{

	// Numerical integral between upper and lower bounds xlow and xhigh
	// xarray = independent variable points (assumed to be increasing between klow and khigh), 
	// yarray = dependent variable points
	// klow, khigh = lowest,highest indicies of interest 

	int i = klow; int j = khigh - 1;
	while (i < khigh && xarray.at(i) < xlow)		// i = first point > lower integration bound
		i++;
	while (j >= klow && xarray.at(i) > xhigh)		// j = last point < upper integration bound
		j--;

	// Interpolate to find values at lower and upper integration bounds
	double y1 = yarray.at(i);
	if (i>klow)   y1 = yarray.at(i) + (yarray.at(i) - yarray.at(i - 1)) / (xarray.at(i) - xarray.at(i - 1)) * (xlow - xarray.at(i));
	double y2 = yarray.at(j);
	if (j<khigh)   y2 = yarray.at(j) + (yarray.at(j) - yarray.at(j + 1)) / (xarray.at(j) - xarray.at(j + 1)) * (xhigh - xarray.at(j));

	double inteval = 0.0;
	for (int k = i; k < j; k++)		// Intergral between tabulated points entirely included in the integration range
		inteval = inteval + (xarray.at(k + 1) - xarray.at(k)) * 0.5 * (yarray.at(k) + yarray.at(k + 1));
	inteval = inteval + (xarray.at(i) - xlow) * 0.5 * (y1 + yarray.at(i));
	if (j >= i)
		inteval = inteval + (xhigh - xarray.at(j)) * 0.5 * (yarray.at(j) + y2);

	return inteval;
}



void C_mspt_receiver_222::calc_ss_profile(const transient_inputs &tinputs, util::matrix_t<double> &tprofile, util::matrix_t<double> &tprofile_wall)
{
	/*=====================================================================================
	Calculate axial temperature profile at steady state
	Temperature is described by PDE: dT/dt + lam1*dT/dz + lam2*T = c with constant parameters lam1, lam2, c

	tinputs:
	inlet_temp = current cold fluid inlet temperature (K)
	npath = number of flow paths
	nelem = total number of flow elements in one flow path (riser and downcomer are included in each flow path)
	nztot = total number of axial evaluation points in one flow path
	length(j) = total length of flow element j (assumed to be the same in each flow path) [m]
	nz(j) = number of axial points for element j (assumed to be the same in each flow path)
	zpts(j) = position of axial point j (0 at inlet of each flow element) [m]
	startpt(j) = index of first point in element j (assumed to be the same in each flow path)
	lam1(j,i) = PDE parameter for element j in flow path i  --> dT/dt + lam1*dT/dz + lam2*T = C
	lam2(j,i) = PDE parameter for element j in flow path i
	cval(j,i) = PDE parameter for element j in flow path i
	Rtube(j,i) = Total thermal resistance for element j in flow path i
	tinit(j,i) = fluid temperature at axial point j in flow path i [K]
	timeavg(j,i) = time averaged fluid outlet temperature for element j in flow path i

	tprofile(j,i) = steady state HTF temperature at axial position j in flow path i
	tprofile_wall(j,i) = steady state wall temperature profile at axial position j in flow path i
	=======================================================================================*/

	int i, j, k, pathid;
	double z, term1;



	if (tinputs.lam1.at(0, 0) == 0.0)		// No mass flow rate 
	{
		for (pathid = 0; pathid < tinputs.npath; pathid++)    // Loop over flow paths 
		{
			for (j = 0; j < tinputs.nelem; j++)						// Loop through elements on flow path
			{
				k = tinputs.startpt.at(j);
				if (j>0)
					tprofile.at(k, pathid) = tprofile.at(k - 1, pathid);	// First point of current element = last point of previous element

				for (i = 1; i < tinputs.nz.at(j); i++)						// Loop through axial positions on flow element j (except for first point)
				{
					if (tinputs.lam2.at(j, pathid) != 0)
						tprofile.at(k + i, pathid) = tinputs.cval.at(j, pathid) / tinputs.lam2.at(j, pathid);
					else					// Note: No steady state temperature exists if lam2 = 0
						tprofile.at(k + i, pathid) = 1.0e6;
				}
			}
		}
	}

	else				// lam1 != 0
	{

		for (pathid = 0; pathid < tinputs.npath; pathid++)    // Loop over flow paths 
		{
			tprofile.at(0, pathid) = tinputs.inlet_temp;
			for (j = 0; j < tinputs.nelem; j++)						// Loop through elements on flow path
			{
				k = tinputs.startpt.at(j);
				if (j>0)
					tprofile.at(k, pathid) = tprofile.at(k - 1, pathid);		// First point of current element = last point of previous element

				for (i = 1; i < tinputs.nz.at(j); i++)						// Loop through axial positions on flow element j (except for first point)
				{
					z = tinputs.zpts.at(k + i);			// Local axial position on element j
					if (tinputs.lam2.at(j, pathid) != 0)
						term1 = tinputs.cval.at(j, pathid) / tinputs.lam2.at(j, pathid) * (1.0 - exp(-tinputs.lam2.at(j, pathid) / tinputs.lam1.at(j, pathid) * z));
					else
						term1 = tinputs.cval.at(j, pathid) / tinputs.lam1.at(j, pathid) * z;
					tprofile.at(k + i, pathid) = term1 + tprofile.at(k, pathid) * exp(-tinputs.lam2.at(j, pathid) / tinputs.lam1.at(j, pathid) * z);
				}
			}
		}

		// Average downcomer T profile calculated from each flow path 
		if (tinputs.npath > 1)
		{
			for (i = 0; i < tinputs.nz.at(tinputs.nelem - 1); i++)		// Loop through downcomer axial positions
			{
				tprofile.at(tinputs.startpt.at(tinputs.nelem - 1) + i, 0) = 0.5*tprofile.at(tinputs.startpt.at(tinputs.nelem - 1) + i, 0) + 0.5*tprofile.at(tinputs.startpt.at(tinputs.nelem - 1) + i, 1);
				tprofile.at(tinputs.startpt.at(tinputs.nelem - 1) + i, 1) = tprofile.at(tinputs.startpt.at(tinputs.nelem - 1) + i, 0);
			}
		}
	}

	// Calculate wall temperature profile
	for (int i = 0; i < m_n_lines; i++)			// Loop through flow paths
	{
		int k = 0;
		for (int j = 0; j < m_n_elem; j++)		// Loop through flow elements
		{
			for (int q = 0; q < tinputs.nz.at(j); q++)
			{
				double Tf = tprofile.at(k, i);
				double qnet = (tinputs.cval.at(j, i) - tinputs.lam2.at(j, i)*Tf) * m_tm.at(j);
				tprofile_wall.at(k, i) = Tf;
				if (m_flowelem_type.at(j, i) >= 0)			// Receiver panel
					tprofile_wall.at(k, i) += qnet / CSP::pi * tinputs.Rtube.at(j, i);
				k += 1;
			}
		}
	}

}

void C_mspt_receiver_222::calc_timeavg_temp(double tstep, const transient_inputs &tinputs, util::matrix_t<double> &timeavg){

	/*=====================================================================================
	Calculate time-averaged outlet temperature for each flow element (receiver panel, downcomer, riser, etc)
	Temperature is described by PDE: dT/dt + lam1*dT/dz + lam2*T = c with constant parameters lam1, lam2, c

	tstep = time step (s)
	tinputs:
	inlet_temp = cold fluid inlet temperature (K)
	npath = number of flow paths
	nelem = total number of flow elements in one flow path (riser and downcomer are included in each flow path)
	nztot = total number of axial evaluation points in one flow path
	length(j) = total length of flow element j (assumed to be the same in each flow path) [m]
	nz(j) = number of axial points for element j (assumed to be the same in each flow path)
	zpts(j) = position of axial point j (0 at inlet of each flow element) [m]
	startpt(j) = index of first point in element j (assumed to be the same in each flow path)
	lam1(j,i) = PDE parameter for element j in flow path i  --> dT/dt + lam1*dT/dz + lam2*T = C
	lam2(j,i) = PDE parameter for element j in flow path i
	cval(j,i) = PDE parameter for element j in flow path i
	tinit(j,i) = fluid temperature at axial point j in flow path i [K]
	timeavg(j,i) = time averaged fluid outlet temperature for element j in flow path i
	=======================================================================================*/

	int s = 0;
	int i, j, k, m, pathid;
	double tsscalc, s1, s2, multval, inteval, exp_eval_k, mval;
	double n_k = 0.0;
	double n_m = 0.0;

	if (tstep < 1.e-3)		// Numerical limit for small time steps: time-average outlet temperature = initial outlet temperature
	{
		for (pathid = 0; pathid < tinputs.npath; pathid++)    // Loop over flow paths 
		{
			for (j = 0; j < tinputs.nelem; j++)				// Loop through elements on flow path
				timeavg.at(j, pathid) = tinputs.tinit.at(tinputs.startpt.at(j) + tinputs.nz.at(j) - 1, pathid);
		}
	}

	else		// Analytical solution for any time step except tstep-->0
	{

		if (tinputs.lam1.at(0, 0) == 0.0)		// No mass flow rate in riser--> No mass flow rate through receiver		
		{
			for (pathid = 0; pathid < tinputs.npath; pathid++)    // Loop over flow paths 
			{
				for (j = 0; j < tinputs.nelem; j++)				// Loop through elements on flow path
				{
					k = tinputs.startpt.at(j) + tinputs.nz.at(j) - 1;		// Index of last axial position in flow element j
					if (tinputs.lam2.at(j, pathid) != 0)
						timeavg.at(j, pathid) = (tinputs.cval.at(j, pathid) / tinputs.lam2.at(j, pathid)) + (tinputs.tinit.at(k, pathid) - tinputs.cval.at(j, pathid) / tinputs.lam2.at(j, pathid)) * (1.0 - exp(-tinputs.lam2.at(j, pathid)*tstep)) / (tstep * tinputs.lam2.at(j, pathid));
					else
						timeavg.at(j, pathid) = tinputs.tinit.at(k, pathid)  + 0.5*tinputs.cval.at(j, pathid)*tstep;
				}
			}
		}


		else			// Mass flow through receiver (lam1!=0)
		{
			util::matrix_t<double> sum1, mult1;
			vector<double> Tint;
			sum1.resize(tinputs.nelem, tinputs.nelem); mult1.resize(tinputs.nelem, tinputs.nelem); Tint.resize(tinputs.nztot);

			for (pathid = 0; pathid < tinputs.npath; pathid++)		// Loop over flow paths (if more than one path exists)
			{
				sum1.fill(0.0); mult1.fill(1.0);

				for (j = 0; j < tinputs.nelem; j++)	// Loop through elements on flow path
				{
					// Evaluate function values needed for integration of initial condition of element j
					for (i = 0; i < tinputs.nz.at(j); i++)
						Tint.at(tinputs.startpt.at(j) + i) = tinputs.tinit.at(tinputs.startpt.at(j) + i, pathid) * exp(tinputs.lam2.at(j, pathid) / tinputs.lam1.at(j, pathid) * tinputs.zpts.at(tinputs.startpt.at(j) + i));

					// Update running totals
					if (j == 0)
					{
						sum1.at(0, 0) = tinputs.length.at(j) / tinputs.lam1.at(j, pathid);
						mult1.at(0, 0) = exp(-tinputs.lam2.at(j, pathid) / tinputs.lam1.at(j, pathid) * tinputs.length.at(j));
					}
					else
					{
						for (k = 0; k <= j; k++)
						{
							sum1.at(k, j) = sum1.at(k, j - 1) + tinputs.length.at(j) / tinputs.lam1.at(j, pathid);
							mult1.at(k, j) = mult1.at(k, j - 1) * exp(-tinputs.lam2.at(j, pathid) / tinputs.lam1.at(j, pathid) * tinputs.length.at(j));
						}
					}

					// Calculate time to reach steady state and find element m for which n_m>0 at the end of the time step
					tsscalc = sum1.at(0, j);	// Time to reach steady state outlet temperature from flow element j (jfull in full array containing both flow paths)
					m = -1;
					if (tstep < tsscalc)			// Time step is shorter than time required to reach SS
					{
						for (k = j; k >= 0; k--)	// Loop backwards through flow elements prior to j and find first element m for which n_m>0
						{
							n_k = tinputs.lam1.at(k, pathid) * (sum1.at(k, j) - tstep);
							if (n_k > 0)
								break;
						}
						n_m = n_k;
						m = k;
					}

					// Evaluate time-averaged temperature
					s1 = 0.0;
					for (k = m + 1; k <= j; k++)
					{
						multval = 1.0;
						if (k < tinputs.nelem - 1)
							multval = mult1.at(k + 1, j);

						inteval = integrate(0.0, tinputs.length.at(k), tinputs.zpts, Tint, tinputs.startpt.at(k), tinputs.startpt.at(k) + tinputs.nz.at(k) - 1);		// Integral of initial T*exp(lam2/lam1*z) over full axial coordinate of element k
						exp_eval_k = exp(-tinputs.lam2.at(k, pathid) / tinputs.lam1.at(k, pathid) * tinputs.length.at(k));	// e^(-lam2/lam1 * L) for element k

						if (tinputs.lam2.at(k, pathid) != 0.0)
							s1 = s1 + multval * (tinputs.cval.at(k, pathid) / tinputs.lam2.at(k, pathid) * (1.0 - exp_eval_k) * (tstep - sum1.at(k, j) - 1.0 / tinputs.lam2.at(k, pathid)) + tinputs.cval.at(k, pathid)*tinputs.length.at(k) / (tinputs.lam2.at(k, pathid)*tinputs.lam1.at(k, pathid)) + inteval*exp_eval_k / tinputs.lam1.at(k, pathid));
						else
							s1 = s1 + multval * (tinputs.cval.at(k, pathid) / tinputs.lam1.at(k, pathid) * tinputs.length.at(k) * (tstep - sum1.at(k, j)) + inteval*exp_eval_k / tinputs.lam1.at(k, pathid));
					}

					multval = 1.0;
					if (m < tinputs.nelem - 1)
						multval = mult1.at(m + 1, j);

					if (tstep >= tsscalc)			// Time step is longer than time required to reach SS outlet temperature
						mval = tinputs.inlet_temp * (tstep - tsscalc);
					else					// Time step is shorter than time required to reach SS outlet temperature 
					{
						s2 = 0.0;
						if (m < tinputs.nelem - 1)
							s2 = sum1.at(m + 1, j);
						inteval = integrate(n_m, tinputs.length.at(m), tinputs.zpts, Tint, tinputs.startpt.at(m), tinputs.startpt.at(m) + tinputs.nz.at(m) - 1);		// Integral of initial T*exp(lam2/lam1*z) between n_m and L
						if (tinputs.lam2.at(m, pathid) != 0)
							mval = tinputs.cval.at(m, pathid) / tinputs.lam2.at(m, pathid) * (tstep - s2 - 1.0 / tinputs.lam2.at(m, pathid) * (1 - exp(-tinputs.lam2.at(m, pathid)*(tstep - s2)))) + inteval*exp(-tinputs.lam2.at(m, pathid) / tinputs.lam1.at(m, pathid)*tinputs.length.at(m)) / tinputs.lam1.at(m, pathid);
						else
							mval = -0.5*tinputs.cval.at(m, pathid)*(tstep - s2)*(tstep - s2) + inteval*exp(-tinputs.lam2.at(m, pathid) / tinputs.lam1.at(m, pathid)*tinputs.length.at(m)) / tinputs.lam1.at(m, pathid);
					}
					timeavg.at(j, pathid) = (1.0 / tstep) * (s1 + multval * mval);

				} // Ends loop over flow elements
			} //Ends loop over flow path

			// Average downcomer time-average temperature over flow paths
			if (tinputs.npath > 1)			// More than one flow path feed into downcomer : Downcomer T = average of values calculated individually for each flow path
			{
				timeavg.at(tinputs.nelem - 1, 0) = 0.5*(timeavg.at(tinputs.nelem - 1, 0) + timeavg.at(tinputs.nelem - 1, 1));		// Replace calculated downcomer T with average over flow paths
				timeavg.at(tinputs.nelem - 1, 1) = timeavg.at(tinputs.nelem - 1, 0);
			}
		}
	}
}

void C_mspt_receiver_222::calc_axial_profile(double tpt, const transient_inputs &tinputs, util::matrix_t<double> &tprofile){

	/*=====================================================================================
	Calculate axial temperature profile in each flow path at a given time point
	Temperature is described by PDE: dT/dt + lam1*dT/dz + lam2*T = c with constant parameters lam1, lam2, c

	
	tpt = time (s)
	tinputs:
	inlet_temp = cold fluid inlet temperature (K)
	npath = number of flow paths
	nelem = total number of flow elements in one flow path (riser and downcomer are included in each flow path)
	nztot = total number of axial evaluation points in one flow path
	length(j) = total length of flow element j (assumed to be the same in each flow path) [m]
	nz(j) = number of axial points for element j (assumed to be the same in each flow path)
	zpts(j) = position of axial point j (0 at inlet of each flow element) [m]
	startpt(j) = index of first point in element j (assumed to be the same in each flow path)
	lam1(j,i) = PDE parameter for element j in flow path i  --> dT/dt + lam1*dT/dz + lam2*T = C
	lam2(j,i) = PDE parameter for element j in flow path i
	cval(j,i) = PDE parameter for element j in flow path i
	tinit(j,i) = fluid temperature at axial point j in flow path i [K]
	timeavg(j,i) = time averaged fluid outlet temperature for element j in flow path i

	tprofile(j,i) = HTF temperature at axial position j in flow path i
	=======================================================================================*/

	int s = 0;
	int i, j, k, m, pathid;
	double z, nval, Tval, term2, nk, tk;


	if (tinputs.lam1.at(0, 0) == 0.0)		// No mass flow rate in riser--> No mass flow rate through receiver		
	{
		for (pathid = 0; pathid < tinputs.npath; pathid++)  // Loop over flow paths 
		{
			for (j = 0; j < tinputs.nelem; j++)				// Loop through elements on flow path
			{
				for (i = 0; i < tinputs.nz.at(j); i++)		// Loop through axial positions on flow element j (except for first point)
				{
					k = tinputs.startpt.at(j);				// Index of first axial position in flow element j
					if (tinputs.lam2.at(j, pathid) != 0)
						tprofile.at(k + i, pathid) = tinputs.cval.at(j, pathid) / tinputs.lam2.at(j, pathid) * (1.0 - exp(-tinputs.lam2.at(j, pathid)*tpt)) + tinputs.tinit.at(k + i, pathid)*exp(-tinputs.lam2.at(j, pathid)*tpt);
					else
						tprofile.at(k + i, pathid) = tinputs.tinit.at(k + i, pathid) + tinputs.cval.at(j, pathid)*tpt;
				}
			}
		}
	}


	else		// lam1 != 0
	{
		util::matrix_t<double> sum1, sum2, mult1;
		vector<double> term1, tempinterp, tcrit;
		sum1.resize(tinputs.nelem, tinputs.nelem); sum2.resize(tinputs.nelem, tinputs.nelem); mult1.resize(tinputs.nelem, tinputs.nelem); term1.resize(tinputs.nelem); tcrit.resize(tinputs.nelem);
		tempinterp.resize(tinputs.nztot);

		for (pathid = 0; pathid < tinputs.npath; pathid++)    // Loop over flow paths 
		{
			tprofile.at(0, pathid) = tinputs.inlet_temp;  // First temperature node
			sum1.fill(0.0); sum2.fill(0.0); mult1.fill(1.0);
			for (i = 0; i < tinputs.nztot; i++)
				tempinterp.at(i) = tinputs.tinit.at(i, pathid);

			for (j = 0; j < tinputs.nelem; j++)		// Loop through elements on flow path
			{

				if (tinputs.lam2.at(j, pathid) != 0)
					term1.at(j) = tinputs.cval.at(j, pathid) / tinputs.lam2.at(j, pathid) * (1.0 - exp(-tinputs.lam2.at(j, pathid) / tinputs.lam1.at(j, pathid) * tinputs.length.at(j)));
				else
					term1.at(j) = tinputs.cval.at(j, pathid) / tinputs.lam1.at(j, pathid) * tinputs.length.at(j);

				// Update running total summations and multiplications
				if (j == 0)
				{
					sum1.at(0, 0) = tinputs.length.at(j) / tinputs.lam1.at(j, pathid);
					mult1.at(0, 0) = exp(-tinputs.lam2.at(j, pathid) / tinputs.lam1.at(j, pathid) * tinputs.length.at(j));
					sum2.at(0, 0) = term1.at(j);
				}
				else
				{
					for (k = 0; k <= j; k++){
						sum1.at(k, j) = sum1.at(k, j - 1) + tinputs.length.at(j) / tinputs.lam1.at(j, pathid);
						mult1.at(k, j) = mult1.at(k, j - 1) * exp(-tinputs.lam2.at(j, pathid) / tinputs.lam1.at(j, pathid) * tinputs.length.at(j));
						sum2.at(k, j) = sum2.at(k, j - 1) * exp(-tinputs.lam2.at(j, pathid) / tinputs.lam1.at(j, pathid) * tinputs.length.at(j)) + term1.at(j);
					}
				}

				// Calculate full axial temperature profile at the designated time point tpt
				s = tinputs.nztot*pathid + tinputs.startpt.at(j);		// Index of first axial position on flow element j in path pathid
				if (j > 0)
					tprofile.at(tinputs.startpt.at(j), pathid) = tprofile.at(tinputs.startpt.at(j) - 1, pathid);	// First point of element j = last point of previous element

				for (i = 1; i < tinputs.nz.at(j); i++)		// Loop through axial positions on flow element j (except for first point)
				{
					z = tinputs.zpts.at(tinputs.startpt.at(j) + i);				// Local axial position on element j
					if (tinputs.lam2.at(j, pathid) != 0)
						term2 = tinputs.cval.at(j, pathid) / tinputs.lam2.at(j, pathid) * (1.0 - exp(-tinputs.lam2.at(j, pathid) / tinputs.lam1.at(j, pathid) * z));
					else
						term2 = tinputs.cval.at(j, pathid) / tinputs.lam1.at(j, pathid) * z;

					tcrit.at(0) = z / tinputs.lam1.at(j, pathid);
					m = j;
					while (j > 0 && m >= 0)
					{
						tcrit.at(m) = tcrit.at(0) + sum1.at(m, j - 1);		// tcrit(m) = time at which n_m switches from (+) to (-) --> tcrit(0) = time at which SS is reached at axial point i
						m--;
					}

					if (tcrit.at(j) > tpt)		// n_j > 0
					{
						nval = z - tinputs.lam1.at(j, pathid) * tpt;
						Tval = interpolate(nval, tinputs.zpts, tempinterp, tinputs.startpt.at(j), tinputs.startpt.at(j) + tinputs.nz.at(j) - 1);		// Intial temperature of element j evaluated at point z = nval

						if (tinputs.lam2.at(j, pathid) != 0)
							tprofile.at(tinputs.startpt.at(j) + i, pathid) = tinputs.cval.at(j, pathid) / tinputs.lam2.at(j, pathid) * (1.0 - exp(-tinputs.lam2.at(j, pathid) * tpt)) + Tval*exp(-tinputs.lam2.at(j, pathid) * tpt);
						else
							tprofile.at(tinputs.startpt.at(j) + i, pathid) = tinputs.cval.at(j, pathid) * tpt + Tval*exp(-tinputs.lam2.at(j, pathid) * tpt);
					}
					else
					{
						if (tcrit.at(0) <= tpt)		// Temperature at axial point i has reached SS
						{
							if (j == 0)
								tprofile.at(tinputs.startpt.at(j) + i, pathid) = term2 + exp(-tinputs.lam2.at(j, pathid) / tinputs.lam1.at(j, pathid) * z) * tinputs.inlet_temp;
							else
								tprofile.at(tinputs.startpt.at(j) + i, pathid) = term2 + exp(-tinputs.lam2.at(j, pathid) / tinputs.lam1.at(j, pathid) * z) * (sum2.at(0, j - 1) + tinputs.inlet_temp*mult1.at(0, j - 1));
						}
						else
						{
							for (k = j - 1; k >= 0; k--)
							{
								if (tcrit.at(k) > tpt)
									break;					// k = highest integer element for which tcrit(k) > tpt
							}
							nk = tinputs.lam1.at(k, pathid) * (z / tinputs.lam1.at(j, pathid) + sum1.at(k, j - 1) - tpt);
							tk = tpt - z / tinputs.lam1.at(j, pathid) - sum1.at(k + 1, j - 1);
							Tval = interpolate(nk, tinputs.zpts, tempinterp, tinputs.startpt.at(k), tinputs.startpt.at(k) + tinputs.nz.at(k) - 1);		// Initial temperature of element k evaluated at point z = nk
							if (tinputs.lam2.at(k, pathid) != 0)
								tprofile.at(tinputs.startpt.at(j) + i, pathid) = term2 + exp(-tinputs.lam2.at(j, pathid) / tinputs.lam1.at(j, pathid) * z) * (sum2.at(k + 1, j - 1) + mult1.at(k + 1, j - 1) * (Tval*exp(-tinputs.lam2.at(k, pathid) * tk) + tinputs.cval.at(k, pathid) / tinputs.lam2.at(k, pathid) * (1.0 - exp(-tinputs.lam2.at(k, pathid) * tk))));
							else
								tprofile.at(tinputs.startpt.at(j) + i, pathid) = term2 + exp(-tinputs.lam2.at(j, pathid) / tinputs.lam1.at(j, pathid) * z) * (sum2.at(k + 1, j - 1) + mult1.at(k + 1, j - 1) * (Tval*exp(-tinputs.lam2.at(k, pathid) * tk) + tinputs.cval.at(k, pathid) * tk));
						}
					}
				}		// Ends loop over axial positions
			}		// Ends loop over flow elements
		}		//Ends loop over flow paths

		// Average downcomer T profile if more than one flow path exists
		if (tinputs.npath > 1)
		{
			for (i = 0; i < tinputs.nz.at(tinputs.nelem - 1); i++)		// Loop through downcomer axial positions 
			{
				tprofile.at(tinputs.startpt.at(tinputs.nelem - 1) + i, 0) = 0.5*tprofile.at(tinputs.startpt.at(tinputs.nelem - 1) + i, 0) + 0.5*tprofile.at(tinputs.startpt.at(tinputs.nelem - 1) + i, 1);
				tprofile.at(tinputs.startpt.at(tinputs.nelem - 1) + i, 1) = tprofile.at(tinputs.startpt.at(tinputs.nelem - 1) + i, 0);
			}
		}
	}
}

double C_mspt_receiver_222::calc_single_pt(double tpt, double zpt, int flowid, int pathid, const transient_inputs &tinputs)
{
	/*=====================================================================================
	Calculate HTF temperature at a given time and axial position
	Temperature is described by PDE: dT/dt + lam1*dT/dz + lam2*T = c with constant parameters lam1, lam2, c

	tpt = time (s)
	zpt = local flow element axial position (m): z = 0 at the flow element inlet
	flowid = integer flow element (riser, receiver panel, downcomer, etc.) position in the flow path
	pathid = integer flow path index

	tinputs:
	inlet_temp = cold fluid inlet temperature (K)
	npath = number of flow paths
	nelem = total number of flow elements in one flow path (riser and downcomer are included in each flow path)
	nztot = total number of axial evaluation points in one flow path
	length(j) = total length of flow element j (assumed to be the same in each flow path) [m]
	nz(j) = number of axial points for element j (assumed to be the same in each flow path)
	zpts(j) = position of axial point j (0 at inlet of each flow element) [m]
	startpt(j) = index of first point in element j (assumed to be the same in each flow path)
	lam1(j,i) = PDE parameter for element j in flow path i  --> dT/dt + lam1*dT/dz + lam2*T = C
	lam2(j,i) = PDE parameter for element j in flow path i
	cval(j,i) = PDE parameter for element j in flow path i
	tinit(j,i) = fluid temperature at axial point j in flow path i [K]
	timeavg(j,i) = time averaged fluid outlet temperature for element j in flow path i
	=======================================================================================*/

	int j, k, m;
	double tk, Tval, Tpt;
	double nk = 0.0;

	// Select portion of initial temperature matrix for designated flow path
	vector<double> tempinterp;
	tempinterp.resize(tinputs.nztot);
	for (j = 0; j < tinputs.nztot; j++)
		tempinterp.at(j) = tinputs.tinit.at(j, pathid);


	if (tinputs.lam1.at(0, 0) == 0.0) // No mass flow rate in riser--> No mass flow rate through receiver	
	{
		Tval = interpolate(zpt, tinputs.zpts, tempinterp, tinputs.startpt.at(flowid), tinputs.startpt.at(flowid) + tinputs.nz.at(flowid) - 1);		// Intial temperature evaluated at point z = zpt
		if (tinputs.lam2.at(flowid, pathid) != 0)
			Tpt = tinputs.cval.at(flowid, pathid) / tinputs.lam2.at(flowid, pathid) * (1.0 - exp(-tinputs.lam2.at(flowid, pathid)*tpt)) + Tval*exp(-tinputs.lam2.at(j, pathid)*tpt);
		else
			Tpt = Tval + tinputs.cval.at(j, pathid)*tpt;
	}


	else			// lam1 != 0
	{

		double sum = 0;
		for (k = flowid; k >= 0; k--)		// Loop over flow elements in current flow path <= current element
		{
			nk = tinputs.lam1.at(k, pathid) * (zpt / tinputs.lam1.at(flowid, pathid) - tpt + sum);	// Characteristic value on elemnt k
			if (nk > 0)
				break;
			if (k > 0)
				sum = sum + tinputs.length.at(k - 1) / tinputs.lam1.at(k - 1, pathid);
		}

		double mult2 = 1; double sum2 = 0;
		double mult; double term1;
		if (k == flowid)
		{
			Tval = interpolate(nk, tinputs.zpts, tempinterp, tinputs.startpt.at(k), tinputs.startpt.at(k) + tinputs.nz.at(k) - 1);		// Intial temperature of element j evaluated at point z = nval
			if (tinputs.lam2.at(k, pathid) != 0)
				Tpt = tinputs.cval.at(k, pathid) / tinputs.lam2.at(k, pathid) * (1.0 - exp(-tinputs.lam2.at(k, pathid) * tpt)) + Tval * exp(-tinputs.lam2.at(k, pathid) * tpt);		// Temperature solution
			else
				Tpt = tinputs.cval.at(k, pathid) * tpt + Tval * exp(-tinputs.lam2.at(k, pathid) * tpt);		// Temperature solution
		}
		else
		{
			for (j = k + 1; j < flowid; j++)
			{
				mult = 1;
				for (m = j + 1; m < flowid; m++)
					mult = mult*exp(-tinputs.lam2.at(m, pathid) / tinputs.lam1.at(m, pathid) * tinputs.length.at(m));
				if (tinputs.lam2.at(j, pathid) != 0)
					sum2 = sum2 + tinputs.cval.at(j, pathid) / tinputs.lam2.at(j, pathid) * (1.0 - exp(-tinputs.lam2.at(j, pathid) / tinputs.lam1.at(j, pathid) * tinputs.length.at(j))) * mult;
				else
					sum2 = sum2 + tinputs.cval.at(j, pathid) / tinputs.lam1.at(j, pathid) * tinputs.length.at(j) * mult;
				mult2 = mult2 * exp(-tinputs.lam2.at(j, pathid) / tinputs.lam1.at(j, pathid) * tinputs.length.at(j));
			}

			if (tinputs.lam2.at(flowid, pathid) != 0)
				term1 = tinputs.cval.at(flowid, pathid) / tinputs.lam2.at(flowid, pathid) * (1.0 - exp(-tinputs.lam2.at(flowid, pathid) / tinputs.lam1.at(flowid, pathid) * zpt));
			else
				term1 = tinputs.cval.at(flowid, pathid) / tinputs.lam1.at(flowid, pathid) * zpt;

			if (nk <= 0)			// SS temperature
				Tpt = term1 + exp(-tinputs.lam2.at(flowid, pathid) / tinputs.lam1.at(flowid, pathid) * zpt) * (sum2 + tinputs.inlet_temp*mult2);
			else
			{
				tk = -nk / tinputs.lam1.at(k, pathid) + tinputs.length.at(k) / tinputs.lam1.at(k, pathid);
				Tval = interpolate(nk, tinputs.zpts, tempinterp, tinputs.startpt.at(k), tinputs.startpt.at(k) + tinputs.nz.at(k) - 1);		// Intial temperature of element k evaluated at point z = nval

				if (tinputs.lam2.at(k, pathid) != 0)
					Tpt = term1 + exp(-tinputs.lam2.at(flowid, pathid) / tinputs.lam1.at(flowid, pathid) * zpt) * (sum2 + mult2*(Tval*exp(-tinputs.lam2.at(k, pathid) * tk) + tinputs.cval.at(k, pathid) / tinputs.lam2.at(k, pathid) * (1.0 - exp(-tinputs.lam2.at(k, pathid) * tk))));
				else
					Tpt = term1 + exp(-tinputs.lam2.at(flowid, pathid) / tinputs.lam1.at(flowid, pathid) * zpt) * (sum2 + mult2*(Tval*exp(-tinputs.lam2.at(k, pathid) * tk) + tinputs.cval.at(k, pathid) * tk));
			}
		}
	}

	return Tpt;
}

void C_mspt_receiver_222::calc_extreme_outlet_values(double tstep, const transient_inputs &tinputs, double *tmin, double *tmax, double *tptmin, double *tptmax)
{
	/*=====================================================================================
	Calculate the minimum and maximum outlet temperatures which occur at any point in time within the designated time step
	Temperature is described by PDE: dT/dt + lam1*dT/dz + lam2*T = c with constant parameters lam1, lam2, c

	tstep = time step (s)
	tinputs:
	inlet_temp = cold fluid inlet temperature (K)
	npath = number of flow paths
	nelem = total number of flow elements in one flow path (riser and downcomer are included in each flow path)
	nztot = total number of axial evaluation points in one flow path
	length(j) = total length of flow element j (assumed to be the same in each flow path) [m]
	nz(j) = number of axial points for element j (assumed to be the same in each flow path)
	zpts(j) = position of axial point j (0 at inlet of each flow element) [m]
	startpt(j) = index of first point in element j (assumed to be the same in each flow path)
	lam1(j,i) = PDE parameter for element j in flow path i  --> dT/dt + lam1*dT/dz + lam2*T = C
	lam2(j,i) = PDE parameter for element j in flow path i
	cval(j,i) = PDE parameter for element j in flow path i
	tinit(j,i) = fluid temperature at axial point j in flow path i [K]
	timeavg(j,i) = time averaged fluid outlet temperature for element j in flow path i
	tmin = array containing [0] minimum downcomer outlet T, [1] minimum receiver outlet T from flow path 1, [2] = minimum receiver outlet T from flow path 2
	tmax = array containing [0] maximum downcomer outlet T, [1] maximum receiver outlet T from flow path 1, [2] = maximum receiver outlet T from flow path 2
	tptmin = array of time points at which minimum temperature is achieved for [0] downcomer outlet, [1] receiver outlet from flow path 1, [2] = receiver outlet from flow path 2
	tptmin = array of time points at which maximum temperature is achieved for [0] downcomer outlet, [1] receiver outlet from flow path 1, [2] = receiver outlet from flow path 2

	Note: Calculated values for single downcomer with multiple flow paths are only strictly accurate if parameter lam1 is the same for corresponding elements in each flow path
	=======================================================================================*/

	int i, j, k, m, pathid;
	int r = tinputs.nelem - 2;		// Last receiver panel
	int d = tinputs.nelem - 1;		// Downcomer

	//-------------------------------------------------------------------------------//
	// Calculate min/max values which occur at the start or end of the time step
	// Downcomer
	double t_end;
	tmin[0] = tinputs.tinit.at(tinputs.nztot - 1, 0);
	tmax[0] = tinputs.tinit.at(tinputs.nztot - 1, 0);
	tptmin[0] = 0.0;
	tptmax[0] = 0.0;
	t_end = calc_single_pt(tstep, tinputs.length.at(d), d, 0, tinputs);		// Downcomer outlet T at end of time step
	if (tinputs.npath>1)
		t_end = 0.5 * (t_end + calc_single_pt( tstep, tinputs.length.at(d), d, 1, tinputs));	// Average of outlet temperature from both flow paths
	if (t_end > tmax[0])
	{
		tmax[0] = t_end;
		tptmax[0] = tstep;
	}
	if (t_end < tmin[0])
	{
		tmin[0] = t_end;
		tptmin[0] = tstep;
	}

	//Receiver
	int s = tinputs.startpt.at(r) + tinputs.nz.at(r) - 1;	// Axial point index for receiver outlet
	for (i = 0; i < tinputs.npath; i++)
	{
		tmin[i + 1] = tinputs.tinit.at(s, i);
		tmax[i + 1] = tinputs.tinit.at(s, i);
		tptmin[i + 1] = 0.0;
		tptmax[i + 1] = 0.0;
		t_end = calc_single_pt(tstep, tinputs.length.at(r), r, i, tinputs);		// Receiver flow path i outlet temperature at the end of the time step
		if (t_end > tmax[i + 1])
		{
			tmax[i + 1] = t_end;
			tptmax[i + 1] = tstep;
		}
		if (t_end < tmin[i + 1])
		{
			tmin[i + 1] = t_end;
			tptmin[i + 1] = tstep;
		}
	}


	if (tinputs.lam1.at(0, 0) != 0)		// lam1 > 0 --> There is mass flow through the reciever (No local extreme points are possible without mass flow)
	{
		//------------------------------------------------------------------------------------//
		// Calculate spatial derivatives of the initial condition and test values at each axial position (extreme value occurs where test value = 0)
		double newsign, nj, tpt, tval, dz;
		double currentsign = 0.0;
		double currentsign2 = 0.0;
		util::matrix_t<double> tinitderiv, testval, testval2;
		tinitderiv.resize(tinputs.nztot, tinputs.npath); testval.resize(tinputs.nztot, tinputs.npath); testval2.resize(tinputs.nztot);

		for (pathid = 0; pathid < tinputs.npath; pathid++)		// Loop over flow paths
		{
			for (j = 0; j < tinputs.nelem; j++)				// Loop over flow elements
			{
				if (tinputs.cval.at(j, pathid) != 0 && tinputs.lam2.at(j, pathid) != 0)
				{
					dz = tinputs.length.at(j) / (double)(tinputs.nz.at(j) - 1);	// Distance between axial points
					for (i = 0; i < tinputs.nz.at(j); i++)						// Loop over axial positions
					{
						m = tinputs.startpt.at(j) + i;							// Index for axial position in full array 

						if (i>1 && i < tinputs.nz.at(j) - 2)
							tinitderiv.at(m, pathid) = (-tinputs.tinit.at(m + 2, pathid) + 8 * tinputs.tinit.at(m + 1, pathid) - 8 * tinputs.tinit.at(m - 1, pathid) + tinputs.tinit.at(m - 2, pathid)) / (12.0*dz);
						else
						{
							if (i == 0)		// First node
								tinitderiv.at(m, pathid) = (tinputs.tinit.at(m + 1, pathid) - tinputs.tinit.at(m, pathid)) / dz;
							else
							{
								if (i == tinputs.nz.at(j) - 1)	// Last node
									tinitderiv.at(m, pathid) = (tinputs.tinit.at(m, pathid) - tinputs.tinit.at(m - 1, pathid)) / dz;
								else
									tinitderiv.at(m, pathid) = (tinputs.tinit.at(m + 1, pathid) - tinputs.tinit.at(m - 1, pathid)) / (2 * dz);
							}
						}

						// Check for change in sign of testvalue between current and previous position
						testval.at(m, pathid) = tinputs.cval.at(j, pathid) - tinputs.lam2.at(j, pathid) * tinputs.tinit.at(m, pathid) - tinputs.lam1.at(j, pathid) * tinitderiv.at(m, pathid);

						if (j == 0 && i == 0)
							currentsign = (testval.at(m, pathid) > 0) - (testval.at(m, pathid) < 0);		// Sign of test value at point s
						else
						{
							newsign = (testval.at(m, pathid) > 0) - (testval.at(m, pathid) < 0);
							if (newsign != currentsign)
							{
								currentsign = newsign;
								nj = 0;
								if (i > 0)
									nj = tinputs.zpts.at(m) - testval.at(m, pathid) * dz / (testval.at(m, pathid) - testval.at(m - 1, pathid));	// nj = approximate axial position where testvalue = 0

								tpt = -nj / tinputs.lam1.at(j, pathid);
								for (k = j; k <= r; k++)
									tpt = tpt + tinputs.length.at(k) / tinputs.lam1.at(k, pathid);		// Time at which extreme value will occur for receiver outlet
								if (tpt<tstep && tpt>0.0)
								{
									tval = calc_single_pt(tpt, tinputs.length.at(r), r, pathid, tinputs);	// Receiver outlet T from flow path pathid at time tpt
									if (tval > tmax[pathid + 1])
									{
										tmax[pathid + 1] = tval;
										tptmax[pathid + 1] = tpt;
									}
									if (tval < tmin[pathid + 1])
									{
										tmin[pathid + 1] = tval;
										tptmin[pathid + 1] = tpt;
									}
								}

								if (tinputs.npath == 1)	// Only one flow path in the receiver --> downcomer extreme temperatures can be calculated directly from single flow path
								{
									tpt = -nj / tinputs.lam1.at(j, pathid);
									for (k = j; k <= d; k++)
										tpt = tpt + tinputs.length.at(k) / tinputs.lam1.at(k, pathid);		// Time at which extreme value will occur for receiver outlet
									if (tpt<tstep&& tpt>0.0)
									{
										tval = calc_single_pt(tpt, tinputs.length.at(d), d, pathid, tinputs);	// Downcomer outlet T at time tpt
										if (tval > tmax[0])
										{
											tmax[0] = tval;
											tptmax[0] = tpt;
										}
										if (tval < tmin[pathid + 1])
										{
											tmin[0] = tval;
											tptmin[0] = tpt;
										}
									}
								}
							}
						}

						if (pathid == 1){		// Second flow path
							// Check for change in sign of testvalue2 between current and previous position
							testval2.at(m) = 0.5*exp(-tinputs.lam2.at(j, 0) / tinputs.lam1.at(j, 0) * (tinputs.length.at(j) - tinputs.zpts.at(m)))*testval.at(m, 0) + 0.5*exp(-tinputs.lam2.at(j, pathid) / tinputs.lam1.at(j, pathid) * (tinputs.length.at(j) - tinputs.zpts.at(m)))*testval.at(m, pathid);
							if (j == 0 && i == 0)
								currentsign2 = (testval2.at(m) > 0) - (testval2.at(m) < 0);		// Sign of test value at point s
							else
							{
								newsign = (testval2.at(m) > 0) - (testval2.at(m) < 0);
								if (newsign != currentsign2)
								{
									currentsign2 = newsign;
									nj = 0;
									if (i > 0)
										nj = tinputs.zpts.at(m) - testval2.at(m) * dz / (testval2.at(m) - testval2.at(m - 1));	// nj = approximate axial position where testvalue2 = 0

									tpt = -nj / tinputs.lam1.at(j, pathid);
									for (k = j; k <= d; k++)
										tpt = tpt + tinputs.length.at(k) / tinputs.lam1.at(k, pathid);		// Time at which extreme value will occur for downcomer outlet
									if (tpt<tstep && tpt>0.0)
									{
										tval = calc_single_pt(tpt, tinputs.length.at(d), d, 0, tinputs);	// Downcomer outlet T calculated from flow path 0
										tval = 0.5*(tval + calc_single_pt(tpt, tinputs.length.at(d), d, 1, tinputs));	// Downcomer outlet T averaged over flow paths
										if (tval > tmax[0])
										{
											tmax[0] = tval;
											tptmax[0] = tpt;
										}
										if (tval < tmin[0])
										{
											tmin[0] = tval;
											tptmin[0] = tpt;
										}
									}
								}
							}
						}
					}	// Ends loop over axial positions
				}
			}		// Ends loop over flow elements
		}			// Ends loop over flow paths
	}
}


void C_mspt_receiver_222::update_pde_parameters(const C_csp_weatherreader::S_outputs &weather, bool use_initial_t, parameter_eval_inputs &pinputs, transient_inputs &tinputs)
{

	//Update PDE parameters and tube wall thermal resistance based on property evaluation temperatures: pinputs.Tfeval and pinputs.Tseval

	/*=============================================================================
	
	use_initial_t = use the temperature profile specified in tinputs.tinit and tinputs.tinit_wall to evaluate pde parameters, overwriting any current inputs in pinputs.Tfeval and pinputs.Tsevel

	pinputs.
	mflow_tot = total HTF mass flow through the receiver (kg/s)
	T_amb = ambient temperature (K)
	T_sky = sky temperature (K)
	c_htf = HTF specific heat evaluated at the avg. of the current inlet and the design point outlet temperatures (J/kg/K)
	rho_htf = HTF density (kg/m3)
	mu_htf = HTF viscosity (kg/m/s)
	k_htf = HTF thermal conductivity (W/m/K)
	Pr_htf = HTF Prandtl number
	tm(j) = thermal mass of element j (assumed to be the same in each flow path) [J/m/K]
	qinc(j,i) = incident solar energy per tube for element j in path i [W]
	Tfeval(j,i) = fluid temperature for element j in flow path i [K]
	Tseval(j,i) = solid temperature for element j in flow path i [K]

	tinputs.
	npath = number of flow paths
	nelem = total number of flow elements in one flow path (riser and downcomer are included in each flow path)
	nztot = total number of axial evaluation points in one flow path
	length(j) = total length of flow element j (assumed to be the same in each flow path) [m]
	nz(j) = number of axial points for element j (assumed to be the same in each flow path)
	zpts(j) = position of axial point j (0 at inlet of each flow element) [m]
	startpt(j) = index of first point in element j (assumed to be the same in each flow path)
	lam1(j,i) = PDE parameter for element j in flow path i  --> dT/dt + lam1*dT/dz + lam2*T = C
	lam2(j,i) = PDE parameter for element j in flow path i  --> dT/dt + lam1*dT/dz + lam2*T = C
	cval(j,i) = PDE parameter for element j in flow path i --> dT/dt + lam1*dT/dz + lam2*T = C
	Rtube = turbe thermal resistance for element j in flow path i
	tinit(j,i) = fluid temperature at axial point j in flow path i [K]

	================================================================================*/

	double mmult, Reelem, Nuelem, felem, hinner, k_tube, Rwall, Rconv;
	double Pr_htf = pinputs.c_htf*pinputs.mu_htf / pinputs.k_htf;
	int i, j;

	tinputs.lam1.fill(0.0);
	tinputs.lam2.fill(0.0);
	tinputs.cval.fill(0.0);
	tinputs.Rtube.fill(0.0);

	for (i = 0; i < m_n_lines; i++)
	{
		for (j = 0; j < m_n_elem; j++)			// Flow path elements in flow order
		{
			if (use_initial_t)   // Overwrite Tfeval and Tseval using values in tinputs.tinit at element midpoint
			{
				int kmid = (int)floor(tinputs.nz.at(j) / 2);
				pinputs.Tfeval.at(j, i) = tinputs.tinit.at(tinputs.startpt.at(j) + kmid, i);	// Initial temperature at midpoint of element j
				pinputs.Tseval.at(j, i) = tinputs.tinit_wall.at(tinputs.startpt.at(j) + kmid, i);	// Initial wall temperature at midpoint of element j
			}

			k_tube = tube_material.cond((pinputs.Tseval.at(j, i) + pinputs.Tfeval.at(j, i)) / 2.0);		//[W/m-K] Thermal conductivity of the tube wall
			Rwall = log(m_od.at(j) / m_id.at(j)) / k_tube;  
			Rconv = 0.0;

			if (pinputs.mflow_tot > 0.0)
			{
				mmult = 1.0 / (double)m_n_lines / (double)m_n_t;		// Flow rate multiplier for individual tube
				if (m_flowelem_type.at(j, i) == -1 || m_flowelem_type.at(j, i) == -2)	// Riser or downcomer
					mmult = 1.0;
				if (m_flowelem_type.at(j, i) == -3)		// Crossover header
					mmult = 1.0 / (double)m_n_lines;

				Reelem = 4 * mmult*pinputs.mflow_tot / (CSP::pi * m_id.at(j)*pinputs.mu_htf);			// Flow Reynolds number in element j
				CSP::PipeFlow(Reelem, Pr_htf, tinputs.length.at(j) / m_id.at(j), (4.5e-5) / m_id.at(j), Nuelem, felem);
				hinner = Nuelem*pinputs.k_htf / m_id.at(j);										// Tube internal heat transfer coefficient [W/m2/K]
				tinputs.lam1.at(j, i) = mmult*pinputs.mflow_tot*pinputs.c_htf / pinputs.tm.at(j);
				Rconv = 1.0 / (0.5*hinner* m_id.at(j));  // Convective resistance between fluid and internal tube wall
			}

			if (m_flowelem_type.at(j, i) >= 0)				// Receiver panel
			{
				int jtube = m_flowelem_type.at(j, i);		//Panel number
				double hmix = calc_external_convection_coeff(weather, pinputs.Tseval.at(j, i));
				double Tlin = pinputs.Tseval.at(j, i);																// Linearization temperature for radiative loss [K]
				double heff = (2.0 / CSP::pi) * m_hl_ffact * (0.5*hmix + 4 * CSP::sigma*m_epsilon*pow(Tlin, 3));	// Effective heat transfer coefficient [W/m2/K]
				double qabstube = pinputs.qinc.at(j, i) / (CSP::pi*0.5*m_od.at(j)*tinputs.length.at(j));				// Solar flux absorbed by one tube [W/m2 tube SA]
				if (pinputs.mflow_tot > 0.0)
					tinputs.Rtube.at(j, i) = Rwall + Rconv; // Total thermal resistance between fluid and front external tube wall	

				tinputs.lam2.at(j, i) = CSP::pi*0.5*m_od.at(j)*heff / (1.0 + 0.5*m_od.at(j)*tinputs.Rtube.at(j, i)*heff) * (1.0 / pinputs.tm.at(j));
				tinputs.cval.at(j, i) = CSP::pi*0.5*m_od.at(j) * (qabstube + (1.0 / CSP::pi)*hmix*m_hl_ffact*pinputs.T_amb + (2.0 / CSP::pi)*m_hl_ffact*m_epsilon*CSP::sigma*(3.0*pow(Tlin, 4) + 0.5*pow(pinputs.T_amb, 4) + 0.5*pow(pinputs.T_sky, 4))) / (1.0 + 0.5*m_od.at(j)*tinputs.Rtube.at(j, i)*heff) * (1.0 / pinputs.tm.at(j));
			}

			if (m_flowelem_type.at(j, i) == -1 || m_flowelem_type.at(j, i) == -2)		// Riser or downcomer
			{
				double Rtot;
				if (m_flowelem_type.at(j, i) == -1)
					Rtot = m_Rtot_riser;   // Thermal resistance between fluid and external tube wall (assumed constant from wetted loss coefficient)
				else
					Rtot = m_Rtot_downc;
				tinputs.lam2.at(j, i) = 2.0*CSP::pi / Rtot / pinputs.tm.at(j);
				tinputs.cval.at(j, i) = 2.0*CSP::pi * pinputs.T_amb / Rtot / pinputs.tm.at(j);
			}
		}
	}

}

void C_mspt_receiver_222::solve_transient_model(const C_csp_weatherreader::S_outputs &weather, 
	double tstep,
	double allowable_Trise,
	parameter_eval_inputs &pinputs,
	transient_inputs &tinputs,
	transient_outputs &toutputs)
{
	/* ===============================================================
	Solve transient receiver model:
	1) Set property evaluation temperatures to values at initial condition
	2) Calculate time averaged outlet temperature from each flow element
	3) Update linearization and property evaluation temperatures based on time-averaged flow element temperature
	4) Update PDE coefficients
	5) Repeat 1-3 until time-averaged temperatures converge
	6) Calculate the maximum temperature change during the time step
	7) Subdivide time step if maximum temperature changes exceeds the specified limiting value and repeat 1-6

	tstep = full time step (s)
	allowable_Trise = maximum allowable change in temperature during the sub-divided time step (for accuracy of linearized radiative losses and analytical formulation)

	pinputs = physical properties and conditions required to evaluate PDE parameters
	tinputs = transient model input parameters
	toutputs = transient model output parameters

	================================================================================*/


	// Initialize output values
	toutputs.timeavg_tout = 0.0;			// Time-averaged downcomer outlet T [K]
	toutputs.tout = 0.0;					// Downcomer outlet T at the end of the time step [K]
	toutputs.max_tout = 0.0;				// Max downcomer outlet T during the time step [K]
	toutputs.min_tout = 5000.0;				// Min downcomer outlet T during the time step [K]
	toutputs.max_rec_tout = 0.0;			// Max receiver outlet T during the time step [K]
	toutputs.timeavg_conv_loss = 0.0;		// Time-averaged convection loss from the receiver panels [W]
	toutputs.timeavg_rad_loss = 0.0;		// Time-averaged radiation loss
	toutputs.timeavg_piping_loss = 0.0;		// Time-averaged thermal loss from piping [W]
	toutputs.timeavg_qthermal = 0.0;		// Average thermal power sent to power cycle or storage during the time step [W]
	toutputs.timeavg_qnet = 0.0;			// Average net thermal power absorbed by the receiver during the time step [W]
	toutputs.t_profile.fill(0.0);			// Axial temperature profile at the end of the time step
	toutputs.t_profile_wall.fill(0.0);			// Axial temperature profile at the end of the time step
	toutputs.timeavg_temp.fill(0.0);		// Time-averaged exit temperature from each flow element [K]
	toutputs.time_min_tout = 0.0;			// Time (relative to beginning of time step) at which minimum downcomer outlet T occurs (s)
	toutputs.tube_temp_inlet = 0.0;
	toutputs.tube_temp_outlet = 0.0;


	// Initialize local variables
	double max_Trise;
	double allowable_min_step = 60.0;		// Minimum allowable time step (s) for solving transient model (transient model time step is only reduced if allowable_Trise is exceeded)
	double transmodel_step = tstep;			// Initial time step for solution of transient model (s)
	double solved_time = 0.0;
	int qsub = 0;							// Iterations to adjust intermediate transient model time steps
	int qmax = 50;							// Max iterations for adjustment of PDE parameters based on iterative solution of time-averaged tempeatures
	util::matrix_t<double>tinit_start = tinputs.tinit;			// Save initial condition at start of full time step 
	util::matrix_t<double>tinit_wall_start = tinputs.tinit_wall;


	// Update PDE parameters using initial temperature solution
	update_pde_parameters(weather, true, pinputs, tinputs);	

	// Solve transient model
	while (solved_time < tstep)	       // Iterations for subdivision of full time step if temperature changes are too large for accuracy of the linearized approximation for radiative loss
	{
		max_Trise = 0.0;

		// Calculate time-averaged temperature and iterate to adjust linearization temperature and properties
		double maxTdiff = 1000.0;
		double Tconverge = 5.0;		// Convergence criteria (K) for change in property evaluation and linearization temperatures between iterations
		double panel_loss_sum, piping_loss_sum, rad_loss_sum, conv_loss_sum, qnet_sum;
		panel_loss_sum = piping_loss_sum = rad_loss_sum = conv_loss_sum = qnet_sum = 0.0;
		int q = 0;
		while (maxTdiff > Tconverge && q < qmax)
		{
			maxTdiff = panel_loss_sum = piping_loss_sum = rad_loss_sum = conv_loss_sum = qnet_sum = 0.0;
			if (q>0)
				update_pde_parameters(weather, false, pinputs, tinputs);				// Update PDE parameters with specified Tfeval and Tseval	
			calc_timeavg_temp(transmodel_step, tinputs, toutputs.timeavg_temp);		// Calculate time-averaged temperature at the outlet of each flow element

			for (int i = 0; i < m_n_lines; i++)			// Loop through flow paths
			{
				for (int j = 0; j < m_n_elem; j++)		// Loop through flow elements
				{
					double Tfnew, Tsnew;
					// Time-averaged inlet temperature for flow element j
					if (pinputs.mflow_tot == 0.0)
						Tfnew = Tsnew = toutputs.timeavg_temp.at(j, i);
					else
					{
						double Tfavg_inlet;
						if (j == 0)
							Tfavg_inlet = tinputs.inlet_temp;
						else
							Tfavg_inlet = toutputs.timeavg_temp.at(j - 1, i);

						if (j == m_n_elem - 1 && m_n_lines > 1)		// Downcomer with more than one flow path
							Tfavg_inlet = 0.5*(toutputs.timeavg_temp.at(j - 1, 0) + toutputs.timeavg_temp.at(j - 1, 1));

						// Time-averaged net heat transfer rate (W/m-length) from linearized approximation: Values for receiver panels are per tube
						double qnet_out = (tinputs.cval.at(j, i) - tinputs.lam2.at(j, i)*toutputs.timeavg_temp.at(j, i)) * m_tm.at(j);		// Value at outlet
						double qnet_in = (tinputs.cval.at(j, i) - tinputs.lam2.at(j, i)*Tfavg_inlet) * m_tm.at(j);							// Value at inlet
						double qnet_avg = 0.5*(qnet_out + qnet_in);
						double Ts_out, Ts_in;

						if (m_flowelem_type.at(j, i) >= 0)			// Receiver panel
						{
							Ts_out = toutputs.timeavg_temp.at(j, i) + qnet_out / CSP::pi * tinputs.Rtube.at(j, i);			// Time-averaged front external wall temperature at the flow element outlet
							Ts_in = Tfavg_inlet + qnet_in / CSP::pi * tinputs.Rtube.at(j, i);								// Time-averaged front external wall temperature at the flow element inlet
							qnet_sum = qnet_sum + qnet_avg*tinputs.length.at(j)*m_n_t;								// Time-averaged net heat transfer rate (W)
							double panel_loss = pinputs.qinc.at(j, i)*m_n_t - qnet_avg*tinputs.length.at(j)*m_n_t;	// Time-averaged loss from panel = absorbed - net [W]
							panel_loss_sum = panel_loss_sum + panel_loss;
							double Ts_avg = 0.5*(Ts_out + Ts_in);
							double Tlin = pinputs.Tseval.at(j, i);
							double panel_rad_loss = m_od.at(j)* m_hl_ffact * m_epsilon*CSP::sigma * (4.0*pow(Tlin, 3.0)*Ts_avg - 3.0 * pow(Tlin, 4.0) - 0.5*pow(pinputs.T_amb, 4.0) - 0.5*pow(pinputs.T_sky, 4.0)) * tinputs.length.at(j)*m_n_t;	// Time-averged radiation loss from panel [W]
							double panel_conv_loss = panel_loss - panel_rad_loss;   // Time-averaged panel convection loss [W] 
							rad_loss_sum = rad_loss_sum + panel_rad_loss;			// Time-averaged total radiative loss from all panels [W]
							conv_loss_sum = conv_loss_sum + panel_conv_loss;		// Time-averaged total convection loss from all panels [W]
						}
						else
						{
							Ts_out = toutputs.timeavg_temp.at(j, i);
							Ts_in = Tfavg_inlet;
							if (i == 0 || m_flowelem_type.at(j, i) == -3)		// First flow path (riser and downcomer solutions are repeated in both flow paths) or crossover header
							{
								qnet_sum = qnet_sum + qnet_avg*tinputs.length.at(j);			// Time-averaged net heat transfer rate (W)
								piping_loss_sum = piping_loss_sum - (qnet_avg*tinputs.length.at(j));
							}
						}
						Tfnew = 0.5*(toutputs.timeavg_temp.at(j, i) + Tfavg_inlet);		// Average fluid temperature within the flow element
						Tsnew = 0.5*(Ts_out + Ts_in);									// Average solid temperature within the flow element
					}

					maxTdiff = fmax(maxTdiff, fmax(fabs(Tsnew - pinputs.Tseval.at(j, i)), fabs(Tfnew - pinputs.Tfeval.at(j, i))));	// Update maximum difference between previous and new average fluid and solid temperatures
					pinputs.Tfeval.at(j, i) = Tfnew;		// Update property evaluation and linearization temperatures
					pinputs.Tseval.at(j, i) = Tsnew;
				}
			}
			q++;
		}
		calc_axial_profile(transmodel_step, tinputs, toutputs.t_profile);		// Calculate full axial temperature profile at the end of the time step

		// Estimate the maximum temperature variation that occurs for any flow element during the time step 
		double tmax[3] = { 0, 0, 0 };
		double tmin[3] = { 0, 0, 0 };
		double tptmin[3] = { 0, 0, 0 };
		double tptmax[3] = { 0, 0, 0 };
		if (pinputs.mflow_tot > 0.0)
		{
			calc_extreme_outlet_values(transmodel_step, tinputs, tmin, tmax, tptmin, tptmax);			// Calculate min/max temperatures which occur at the downcomer and receiver outlet at any point during the time step
			max_Trise = fmax(tmax[0] - tmin[0], fmax(tmax[1] - tmin[1], tmax[2] - tmin[2]));		// Largest difference between max/min values for the receiver outlet or downcomer outlet during the time step
		}
		for (int i = 0; i < m_n_lines; i++)
		{
			for (int j = 0; j < m_nz_tot; j++)
				max_Trise = fmax(max_Trise, fabs(toutputs.t_profile.at(j, i) - tinputs.tinit.at(j, i)));		// Difference between final and initial temperature at axial position j
		}

		// Calculate output values or subdivide time step
		if (max_Trise < allowable_Trise || transmodel_step <= allowable_min_step)				// Maximum temperature variation is acceptable or the time step is the minimum allowable value
		{
			toutputs.timeavg_qnet = toutputs.timeavg_qnet + qnet_sum*(transmodel_step / tstep);
			toutputs.timeavg_rad_loss = toutputs.timeavg_rad_loss + rad_loss_sum*(transmodel_step / tstep);
			toutputs.timeavg_conv_loss = toutputs.timeavg_conv_loss + conv_loss_sum*(transmodel_step / tstep);
			toutputs.timeavg_piping_loss = toutputs.timeavg_piping_loss + piping_loss_sum*(transmodel_step / tstep);
			toutputs.timeavg_tout = toutputs.timeavg_tout + toutputs.timeavg_temp.at(m_n_elem - 1, 0)*(transmodel_step / tstep);
			toutputs.max_tout = fmax(toutputs.max_tout, tmax[0]);
			if (tmin[0] < toutputs.min_tout)
			{
				toutputs.min_tout = tmin[0];
				toutputs.time_min_tout = solved_time + tptmin[0];	// Time relative to beginning of full time step
			}

			toutputs.max_rec_tout = fmax(toutputs.max_rec_tout, tmax[1]);
			if (m_n_lines > 1)
				toutputs.max_rec_tout = fmax(toutputs.max_rec_tout, tmax[2]);

			solved_time = solved_time + transmodel_step;
			if (tstep - solved_time > 0.01)					// The full time step has not been finished
			{
				transmodel_step = tstep - solved_time;		// Set transient model time step = remaining fraction of the full model time step
				tinputs.tinit = toutputs.t_profile;			// Set new initial temperature profile to profile at the end of the last successful transient model time step
				tinputs.tinit_wall = toutputs.t_profile_wall;
			}
		}
		else		// Maximum temperature variation over the transient model time step is not acceptable --> Decrease transient model time step and try again
			transmodel_step = transmodel_step / 2.0;
		qsub++;
	}
	toutputs.tout = toutputs.t_profile.at(m_nz_tot - 1, 0);														// Downcomer outlet T at the end of the time step
	toutputs.timeavg_qthermal = pinputs.mflow_tot * pinputs.c_htf * (toutputs.timeavg_tout - tinputs.inlet_temp);				// Time-averaged thermal power leaving the receiver during the time step [W]	
	tinputs.tinit = tinit_start;		// Revert initial temperature profile back to profile at the start of the full time step (in case the model is called more than once during this time step)
	tinputs.tinit_wall = tinit_wall_start;

	// Calculate receiver wall temperature profile at the end of the time step
	for (int i = 0; i < m_n_lines; i++)			// Loop through flow paths
	{
		int k = 0;
		for (int j = 0; j < m_n_elem; j++)		// Loop through flow elements
		{
			for (int q = 0; q < tinputs.nz.at(j); q++)
			{
				double Tf = toutputs.t_profile.at(k, i);
				double qnet = (tinputs.cval.at(j, i) - tinputs.lam2.at(j, i)*Tf) * m_tm.at(j);
				toutputs.t_profile_wall.at(k, i) = Tf;
				if (m_flowelem_type.at(j, i) >= 0)			// Receiver panel
					toutputs.t_profile_wall.at(k, i) += qnet / CSP::pi * tinputs.Rtube.at(j, i);
				k += 1;
			}
		}
		toutputs.tube_temp_inlet += toutputs.t_profile_wall.at(tinputs.startpt.at(1), i) / double(m_n_lines);
		toutputs.tube_temp_outlet += toutputs.t_profile_wall.at(tinputs.startpt.at(m_n_elem - 1) - 1, i) / double(m_n_lines);
	}
}


void C_mspt_receiver_222::solve_transient_startup_model(const C_csp_weatherreader::S_outputs &weather,
	parameter_eval_inputs &pinputs,
	transient_inputs &tinputs,
	int startup_mode,
	double target_temperature,
	double min_time,
	double max_time,
	transient_outputs &toutputs,
	double &startup_time, 
	double &energy)
{

	switch (startup_mode)
	{
	case HEAT_TRACE:
	{
		double heat_trace_time = 0.0;
		double heat_trace_energy = 0.0;

		// Update PDE parameters
		update_pde_parameters(weather, true, pinputs, tinputs);
		for (int i = 0; i < m_n_lines; i++)
		{
			tinputs.cval.at(0, i) = (m_heat_trace_power + 2.0*CSP::pi*pinputs.T_amb / m_Rtot_riser) / pinputs.tm.at(0);
			tinputs.cval.at(m_n_elem - 1, i) = (m_heat_trace_power + 2.0*CSP::pi*pinputs.T_amb / m_Rtot_downc) / pinputs.tm.at(m_n_elem - 1);
		}

		// Calculate time required to reach target temperature 
		double min_time_heattrace = 1.e10;
		int jfirst, jlast;
		jfirst = jlast = 0;
		for (int j = 0; j < m_n_elem; j = j + m_n_elem - 1)
		{
			double time_req_j;
			if (tinputs.lam2.at(j, 0) == 0.0)			// Case with no heat losses
				time_req_j = (target_temperature - tinputs.tinit.at(tinputs.startpt.at(j), 0)) / tinputs.cval.at(j, 0);
			else
				time_req_j = 1.0 / tinputs.lam2.at(j, 0) * log((tinputs.tinit.at(tinputs.startpt.at(j), 0) - tinputs.cval.at(j, 0) / tinputs.lam2.at(j, 0)) / (target_temperature - tinputs.cval.at(j, 0) / tinputs.lam2.at(j, 0)));

			time_req_j = fmax(0.0, time_req_j);
			time_req_j = fmin(max_time, time_req_j);
			heat_trace_time = fmax(heat_trace_time, time_req_j);			// Total time required for heat tracing stage [s] 
			min_time_heattrace = fmin(min_time_heattrace, time_req_j);		// Time at which riser or downcomer first reaches target T (or end of time step) [s]
			if (min_time_heattrace == time_req_j)
				jfirst = j;
			if (heat_trace_time == time_req_j)
				jlast = j;
		}
		calc_axial_profile(min_time_heattrace, tinputs, toutputs.t_profile);	 // Calculate temperature profile after min_time_heattrace
		toutputs.t_profile_wall = toutputs.t_profile;
		heat_trace_energy += m_heat_trace_power * (tinputs.length.at(0) + tinputs.length.at(m_n_elem - 1)) * min_time_heattrace;		// Energy [J] used for heat tracing 

		// Calculate temperature profile after time period where heat tracing is applied to only one of riser and downcomer
		if (heat_trace_time != min_time_heattrace)
		{
			for (int i = 0; i < m_n_lines; i++)
				tinputs.cval.at(jfirst, i) = tinputs.lam2.at(jfirst, i) * pinputs.T_amb;		// Update ODE parameter for element without heat tracing
			tinputs.tinit = toutputs.t_profile;
			tinputs.tinit_wall = toutputs.t_profile_wall;
			calc_axial_profile((heat_trace_time - min_time_heattrace), tinputs, toutputs.t_profile);				// Calculate axial temperature profile after finishing heat tracing during time step
			toutputs.t_profile_wall = toutputs.t_profile;
			heat_trace_energy += m_heat_trace_power * tinputs.length.at(jlast) * (heat_trace_time - min_time_heattrace);		// Energy [J] used for heat tracing 
		}
		energy = heat_trace_energy;
		startup_time = heat_trace_time;
	}
	break;


	case PREHEAT:
	{
		double preheat_time = 0.0;
		double preheat_energy = 0.0;

		// Recalculate recevier min wall T after heat trace
		double Tmin_rec = 5000.0;
		for (int i = 0; i < m_n_lines; i++)
		{
			for (int j = 0; j < m_n_elem; j++)
			{
				int p1 = tinputs.startpt.at(j);
				if (m_flowelem_type.at(j, i) >= 0)
				{
					double Twall_min = fmin(tinputs.tinit.at(p1, i), tinputs.tinit.at(p1 + tinputs.nz.at(j) - 1, i));
					Tmin_rec = fmin(Tmin_rec, Twall_min);
					pinputs.Tseval.at(j, i) = 0.5*(tinputs.tinit.at(p1, i) + target_temperature);
				}
				else
					pinputs.Tseval.at(j, i) = tinputs.tinit.at(p1, i);
			}
		}
		pinputs.Tfeval = pinputs.Tseval;
		update_pde_parameters(weather, false, pinputs, tinputs);	// Update parameters for startup conditions using specified Tfeval and Tseval

		// Calculate required preheating time
		if (tinputs.lam2.at(1, 0) == 0.0)		// No heat losses
			preheat_time = (target_temperature - Tmin_rec) / tinputs.cval.at(1, 0);
		else
		{
			double preheat_ss_temp = tinputs.cval.at(1, 0) / tinputs.lam2.at(1, 0);		// Steady state temperature during preheating
			if (preheat_ss_temp > target_temperature)										// Steady state temperature exceeds preheat target
				preheat_time = 1.0 / tinputs.lam2.at(1, 0) * log((Tmin_rec - tinputs.cval.at(1, 0) / tinputs.lam2.at(1, 0)) / (target_temperature - tinputs.cval.at(1, 0) / tinputs.lam2.at(1, 0)));
			else				// Steady state temperature is below preheat target
				preheat_time = max_time;
		}

		preheat_time = fmin(preheat_time, max_time);					// Time that preheating is applied during the current time step [s]
		calc_axial_profile(preheat_time, tinputs, toutputs.t_profile);	// Calculate axial temperature profiles after preheating 
		toutputs.t_profile_wall = toutputs.t_profile;
		preheat_energy = (pinputs.qinc.at(1, 0)*m_n_panels) * preheat_time;	// Energy [J] used for startup during the time step
		energy = preheat_energy;
		startup_time = preheat_time;
	}
	break;


	case CIRCULATE:
	{
		double circulate_time = 0.0;
		double circulate_energy = 0.0;
		double max_Trise = 150.0;

		// Estimate time required to reach SS downcomer outlet T
		update_pde_parameters(weather, true, pinputs, tinputs);  // only need lam1 --> no temperature dependence
		double time_ss_outlet = 0.0;
		double time_ss_receiver = 0.0;
		for (int i = 0; i < m_n_lines; i++)
		{
			double time_ss = 0.0;
			for (int j = 0; j < m_n_elem - 1; j++)
				time_ss = time_ss + tinputs.length.at(j) / tinputs.lam1.at(j, i);	// Time to reach steady state temperature at the receiver outlet [s] 
			double time_ss_d = time_ss + tinputs.length.at(m_n_elem - 1) / tinputs.lam1.at(m_n_elem - 1, i);		// Time to reach steady state temperature at the downcomer outlet [s] --> Upper bound for end of circulation startup stage
			time_ss_receiver = fmax(time_ss_receiver, time_ss);
			time_ss_outlet = fmax(time_ss_outlet, time_ss_d);
		}

		// Find time at which outlet temperature reaches target value 
		double temp_tol = 2.0;
		double time_tol = 15.0;
		double upperbound = fmin(time_ss_outlet, max_time);	// Upper bound for circulation time = time for downcomer outlet to reach SS
		double lowerbound = fmin(time_ss_receiver - (tinputs.length.at(0) / tinputs.lam1.at(0, 0)), max_time);	// Lower bound for circulation time 
		if (min_time > 0.01)
			lowerbound = fmin(min_time, max_time);		// Redefine lower bound if previously defined from "Hold" mode

		upperbound = fmax(upperbound, lowerbound);
		circulate_time = upperbound;
		solve_transient_model(weather, circulate_time, max_Trise, pinputs, tinputs, toutputs);		// Solve transient model with upper bound for circulation time

		if (toutputs.tout < target_temperature)	// Target outlet temperature not achieved within the current time step
			circulate_time = max_time;
		else	// Target outlet temperature can be achieved within the current time step
		{
			if (toutputs.min_tout < target_temperature)		// Outlet temperature drops below the target during the time step --> set lower bound to time when minimum outlet T occurs
				lowerbound = fmax(lowerbound, toutputs.time_min_tout);

			double Tdiff = toutputs.tout - target_temperature;
			while ((Tdiff < 0.0 || Tdiff > temp_tol) && (upperbound - lowerbound > time_tol))	// Outlet temperature is less than the target, or greater than the target by more than the designated tolerance
			{
				circulate_time = 0.5*(upperbound + lowerbound);
				solve_transient_model(weather, circulate_time, max_Trise, pinputs, tinputs, toutputs);
				Tdiff = toutputs.tout - target_temperature;
				if (Tdiff < 0.0)
					lowerbound = circulate_time;
				else
					upperbound = circulate_time;
			}
		}

		circulate_energy = toutputs.timeavg_qnet * circulate_time; // Energy [J] used for startup during the time step
		energy = circulate_energy;
		startup_time = circulate_time;
	}
	break;

	}

}



void C_mspt_receiver_222::est_startup_time_energy(double fract, double &est_time, double &est_energy)
{
	// Typical conditions during startup  
	double Tamb = 290.0;				// Ambient temperature (K)
	double massflow_fraction = fract;   // Fraction of design point mass flow 

	double cval, time_heattrace, time_preheat, time_circulate, time_startup;
	double T_coolant_prop = 0.5*(m_T_htf_cold_des + m_T_htf_hot_des);

	// Heat tracing (without losses)
	cval = m_heat_trace_power / m_tm_solid.at(0);
	time_heattrace = (m_T_htf_cold_des - Tamb) / cval;

	//Preheating (without losses)
	cval = m_od_tube * m_tube_flux_startup*1000.0 / m_tm_solid.at(1);
	time_preheat = (m_T_htf_cold_des - Tamb) / cval;

	// Circulation (excluding cross-over header)
	double cp_htf = field_htfProps.Cp(T_coolant_prop)*1000.0;		// HTF specific heat at average temperature [J/kg-K] 
	double m_dot_rec_des = m_q_rec_des / (cp_htf*(m_T_htf_hot_des - m_T_htf_cold_des)); // Design point receiver mass flow rate (kg/s)
	double mdot_startup = massflow_fraction*m_dot_rec_des;								// Typical total mass flow rate during startup (kg/s)
	double tube_lam1 = (mdot_startup / m_n_lines / m_n_t)*cp_htf / m_tm.at(1);
	double downc_lam1 = mdot_startup*cp_htf / m_tm.at(m_n_elem - 1);
	time_circulate = (m_n_panels / m_n_lines)*m_h_rec / tube_lam1 + 0.5*(m_h_tower*m_pipe_length_mult + m_pipe_length_add) / downc_lam1;

	time_startup = time_heattrace + time_preheat + time_circulate;
	time_startup = fmax(time_startup, m_rec_su_delay*3600.0);

	est_time = time_startup;
	est_energy = (time_preheat*(m_tube_flux_startup *1000.0* m_od_tube * m_h_rec * m_n_t * m_n_panels) + time_circulate*(m_q_rec_des*massflow_fraction)) * 1.e-6 / 3600.0;		//Energy utilized during the estimated startup time (MWt-hr)

}


double C_mspt_receiver_222::est_heattrace_energy()
{
	double Tamb = 290.0;				// Typical ambient temperature (K) during startup
	if (m_is_startup_transient)			// Heat trace parasitic is only included if the transient startup model is activated
	{
		double riser_tm = m_tm_solid.at(0) * trans_inputs.length.at(0);						// Riser tube thermal mass (J/K)
		double downc_tm = m_tm_solid.at(m_n_elem - 1)* trans_inputs.length.at(m_n_elem - 1);	// Downcomer tube thermal mass (J/K)
		double heattrace_energy = (riser_tm + downc_tm) * (m_T_htf_cold_des - Tamb);	// Energy (J) needed to raise riser and downcomer from ambient T to target T
		return heattrace_energy*1e-6 / 3600.;											// MW-hr
	}
	else
		return 0.0;

}