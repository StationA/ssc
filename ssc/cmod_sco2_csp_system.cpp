#include "core.h"

#include "sco2_pc_csp_int.h"

static var_info _cm_vtab_sco2_csp_system[] = {

	/*   VARTYPE   DATATYPE         NAME               LABEL                                                    UNITS     META  GROUP REQUIRED_IF CONSTRAINTS     UI_HINTS*/
	// ** Design Parameters **
		// System Design
	{ SSC_INPUT,  SSC_NUMBER,  "htf",                  "Integer code for HTF used in PHX",                       "",           "",    "",      "*",     "",       "" },
    { SSC_INPUT,  SSC_MATRIX,  "htf_props",            "User defined HTF property data",                         "", "7 columns (T,Cp,dens,visc,kvisc,cond,h), at least 3 rows", "", "*", "", "" },
	{ SSC_INPUT,  SSC_NUMBER,  "T_htf_hot_des",        "HTF design hot temperature (PHX inlet)",                 "C",          "",    "",      "*",     "",       "" },
	{ SSC_INPUT,  SSC_NUMBER,  "dT_PHX_hot_approach",  "Temp diff btw hot HTF and turbine inlet",                "C",          "",    "",      "*",     "",       "" },
	{ SSC_INPUT,  SSC_NUMBER,  "T_amb_des",            "Ambient temperature",                                    "C",          "",    "",      "*",     "",       "" },
	{ SSC_INPUT,  SSC_NUMBER,  "dT_mc_approach",       "Temp diff btw ambient air and main compressor inlet",    "C",          "",    "",      "*",     "",       "" },
	{ SSC_INPUT,  SSC_NUMBER,  "site_elevation",       "Site elevation",                                         "m",          "",    "",      "*",     "",       "" },
	{ SSC_INPUT,  SSC_NUMBER,  "W_dot_net_des",        "Design cycle power output (no cooling parasitics)",      "MWe",        "",    "",      "*",     "",       "" },
	{ SSC_INPUT,  SSC_NUMBER,  "eta_thermal_des",      "Power cycle thermal efficiency",                         "",           "",    "",      "*",     "",       "" },
		// Cycle Design
	{ SSC_INPUT,  SSC_NUMBER,  "eta_isen_mc",          "Design main compressor isentropic efficiency",           "-",          "",    "",      "*",     "",       "" },
	{ SSC_INPUT,  SSC_NUMBER,  "eta_isen_rc",          "Design re-compressor isentropic efficiency",             "-",          "",    "",      "*",     "",       "" },
	{ SSC_INPUT,  SSC_NUMBER,  "eta_isen_t",           "Design turbine isentropic efficiency",                   "-",          "",    "",      "*",     "",       "" },
	{ SSC_INPUT,  SSC_NUMBER,  "P_high_limit",         "High pressure limit in cycle",                           "MPa",        "",    "",      "*",     "",       "" },
		// PHX Design
	{ SSC_INPUT,  SSC_NUMBER,  "dT_PHX_cold_approach", "Temp diff btw cold HTF and cold CO2",                    "C",          "",    "",      "*",     "",       "" },
		// Air Cooler Design
	{ SSC_INPUT,  SSC_NUMBER,  "fan_power_frac",       "Fraction of net cycle power consumed by air cooler fan", "",           "",    "",      "*",     "",       "" },
	{ SSC_INPUT,  SSC_NUMBER,  "deltaP_cooler_frac",   "Fraction of cycle high pressure that is design point cooler CO2 pressure drop", "", "", "", "*","",       "" },
	// ** Off-design Inputs **
	{ SSC_INPUT,  SSC_NUMBER,  "is_m_dot_htf_fracs",   "0 = No analysis of HTF off design mass flow rate, 1 = Yes", "",        "",    "",      "*",     "",       "" },
	{ SSC_INPUT,  SSC_ARRAY,   "m_dot_htf_fracs_in",   "Array of normalized mass flow rate",                     "",           "",    "",      "is_m_dot_htf_fracs=1",     "",       "" },
	{ SSC_INPUT,  SSC_NUMBER,  "is_T_amb_od",          "0 = N analysis of off design ambient temperature, 1 = Yes", "",        "",    "",      "*",     "",       "" },
	{ SSC_INPUT,  SSC_ARRAY,   "T_amb_od_in",          "Array of ambient temperatures for off-design parametric","C",          "",    "",      "is_T_amb_od=1",     "",       "" },
	// ** Design OUTPUTS **
		// System Design Solution
	{ SSC_OUTPUT, SSC_NUMBER,  "T_htf_cold_des",       "HTF design colde temperature (PHX outlet)",              "C",          "",    "",      "*",     "",       "" },
	{ SSC_OUTPUT, SSC_NUMBER,  "m_dot_htf_des",        "HTF mass flow rate",                                     "kg/s",       "",    "",      "*",     "",       "" },
		// Cycle Design Solution																				 
	{ SSC_OUTPUT, SSC_NUMBER,  "eta_thermal_calc",     "Calculated cycle thermal efficiency",                    "-",          "",    "",      "*",     "",       "" },
	{ SSC_OUTPUT, SSC_NUMBER,  "UA_recup_total",       "Total recuperator UA",                                   "kW/K",       "",    "",      "*",     "",       "" },
	{ SSC_OUTPUT, SSC_NUMBER,  "UA_LTR",               "Low temp recuperator UA",                                "kW/K",       "",    "",      "*",     "",       "" },
	{ SSC_OUTPUT, SSC_NUMBER,  "UA_HTR",               "High temp recuperator UA",                               "kW/K",       "",    "",      "*",     "",       "" },
	{ SSC_OUTPUT, SSC_NUMBER,  "recomp_frac",          "Recompression fraction",                                 "-",          "",    "",      "*",     "",       "" },
	{ SSC_OUTPUT, SSC_NUMBER,  "P_comp_in",            "Compressor inlet pressure",                              "MPa",        "",    "",      "*",     "",       "" },
	{ SSC_OUTPUT, SSC_NUMBER,  "P_comp_out",           "Compressor outlet pressure",                             "MPa",        "",    "",      "*",     "",       "" },
		// PHX Design Solution
	{ SSC_OUTPUT, SSC_NUMBER,  "UA_PHX",               "PHX Conductance",                                        "kW/K",       "",    "",      "*",     "",       "" },
	{ SSC_OUTPUT, SSC_NUMBER,  "eff_PHX",              "PHX effectiveness",                                      "",           "",    "",      "*",     "",       "" },
	{ SSC_OUTPUT, SSC_NUMBER,  "NTU_PHX",              "PHX NTU",                                                "",           "",    "",      "*",     "",       "" },
		// Air Cooler Design
	// ?????

	// ** Off-Design Outputs
	{ SSC_OUTPUT, SSC_ARRAY,   "m_dot_htf_fracs",      "Normalized mass flow rate",                              "",           "",    "",      "*",     "",       "" },
	{ SSC_OUTPUT, SSC_ARRAY,   "T_amb_od",             "Ambient temperatures",                                   "C",          "",    "",      "*",     "",       "" },
	{ SSC_OUTPUT, SSC_ARRAY,   "T_htf_hot_od",         "HTF hot temperatures",                                   "C",          "",    "",      "*",     "",       "" },
	{ SSC_OUTPUT, SSC_ARRAY,   "P_comp_in_od",         "Main compressor inlet pressures",                        "MPa",        "",    "",      "*",     "",       "" },
	{ SSC_OUTPUT, SSC_ARRAY,   "N_mc_od",              "Main compressor speed",                                  "rpm",        "",    "",      "*",     "",       "" },
	{ SSC_OUTPUT, SSC_ARRAY,   "recomp_frac_od",       "Recompression fractions",                                "",           "",    "",      "*",     "",       "" },
	{ SSC_OUTPUT, SSC_ARRAY,   "eta_thermal_od",       "Off-design cycle thermal efficiency",                    "",           "",    "",      "*",     "",       "" },






	var_info_invalid };

int test_mono_function(double x, double *y);

class cm_sco2_csp_system : public compute_module
{
public:

	cm_sco2_csp_system()
	{
		add_var_info(_cm_vtab_sco2_csp_system);
	}

	void exec() throw(general_error)
	{
		C_sco2_recomp_csp::S_des_par sco2_rc_des_par;
			// System design parameters
		sco2_rc_des_par.m_hot_fl_code = as_integer("htf");							//[-] Integer code for HTF
		sco2_rc_des_par.mc_hot_fl_props = as_matrix("htf_props");					//[-] Custom HTF properties
		sco2_rc_des_par.m_T_htf_hot_in = as_double("T_htf_hot_des")+273.15;			//[K] Convert from C
		sco2_rc_des_par.m_phx_dt_hot_approach = as_double("dT_PHX_hot_approach");	//[K/C] Temperature difference between hot HTF and turbine CO2 inlet
		sco2_rc_des_par.m_T_amb_des = as_double("T_amb_des")+273.15;				//[K] Convert from C
		sco2_rc_des_par.m_dt_mc_approach = as_double("dT_mc_approach");				//[K/C] Temperature difference between ambient air and main compressor inlet
		sco2_rc_des_par.m_elevation = as_double("site_elevation");					//[m] Site elevation
		sco2_rc_des_par.m_W_dot_net = as_double("W_dot_net_des")*1000.0;			//[kWe] Convert from MWe, cycle power output w/o cooling parasitics
		sco2_rc_des_par.m_eta_thermal = as_double("eta_thermal_des");				//[-] Cycle thermal efficiency
			
			// Cycle design parameters: hardcode pressure drops, for now
		// Define hardcoded sco2 design point parameters
		std::vector<double> DP_LT(2);
		/*(cold, hot) positive values are absolute [kPa], negative values are relative (-)*/
		DP_LT[0] = 0;
		DP_LT[1] = 0;
		/*(cold, hot) positive values are absolute [kPa], negative values are relative (-)*/
		std::vector<double> DP_HT(2);
		DP_HT[0] = 0;
		DP_HT[1] = 0;
		/*(cold, hot) positive values are absolute [kPa], negative values are relative (-)*/
		std::vector<double> DP_PC(2);
		DP_PC[0] = 0;
		DP_PC[1] = 0;
		/*(cold, hot) positive values are absolute [kPa], negative values are relative (-)*/
		std::vector<double> DP_PHX(2);
		DP_PHX[0] = 0;
		DP_PHX[1] = 0;
		sco2_rc_des_par.m_DP_LT = DP_LT;
		sco2_rc_des_par.m_DP_HT = DP_HT;
		sco2_rc_des_par.m_DP_PC = DP_PC;
		sco2_rc_des_par.m_DP_PHX = DP_PHX;
		sco2_rc_des_par.m_N_sub_hxrs = 10;
		sco2_rc_des_par.m_N_turbine = 3600.0;
		sco2_rc_des_par.m_tol = 1.E-3;
		sco2_rc_des_par.m_opt_tol = 1.E-3;
		
			// Remaining cycle design parameters	
		sco2_rc_des_par.m_eta_mc = as_double("eta_isen_mc");
		sco2_rc_des_par.m_eta_rc = as_double("eta_isen_rc");
		sco2_rc_des_par.m_eta_t = as_double("eta_isen_t");
		sco2_rc_des_par.m_P_high_limit = as_double("P_high_limit")*1000.0;		//[kPa], convert from MPa		
			
			// PHX design parameters
		sco2_rc_des_par.m_phx_dt_cold_approach = as_double("dT_PHX_cold_approach");
			
			// Air cooler parameters
		sco2_rc_des_par.m_frac_fan_power = as_double("fan_power_frac");
		sco2_rc_des_par.m_deltaP_cooler_frac = as_double("deltaP_cooler_frac");

		// For try/catch below
		int out_type = -1;
		std::string out_msg = "";

		// Construction class and design system
		C_sco2_recomp_csp sco2_recomp_csp;
		try
		{
			sco2_recomp_csp.design(sco2_rc_des_par);
		}
		catch( C_csp_exception &csp_exception )
		{
			// Report warning before exiting with error
			while( sco2_recomp_csp.mc_messages.get_message(&out_type, &out_msg))
			{
				log(out_msg);
			}

			log(csp_exception.m_error_message, SSC_ERROR, -1.0);

			return;
		}

		// Set SSC design outputs
			// System
		double m_dot_htf_design = sco2_recomp_csp.get_phx_des_par()->m_m_dot_hot_des;	//[kg/s]
		double T_htf_cold_calc = sco2_recomp_csp.get_design_solved()->ms_phx_des_solved.m_T_h_out;		//[K]
		assign("T_htf_cold_des",T_htf_cold_calc-273.15);		//[C] convert from K
		assign("m_dot_htf_des",m_dot_htf_design);				//[kg/s]
			// Cycle
		assign("eta_thermal_calc",sco2_recomp_csp.get_design_solved()->ms_rc_cycle_solved.m_eta_thermal);	//[-]
		double UA_LTR = sco2_recomp_csp.get_design_solved()->ms_rc_cycle_solved.m_UA_LT;		//[kW/K]
		double UA_HTR = sco2_recomp_csp.get_design_solved()->ms_rc_cycle_solved.m_UA_HT;		//[kW/K]
		assign("UA_recup_total",UA_LTR + UA_HTR);		//[kW/K]
		assign("UA_LTR",UA_LTR);						//[kW/K]
		assign("UA_HTR",UA_HTR);						//[kW/K]
		assign("recomp_frac",sco2_recomp_csp.get_design_solved()->ms_rc_cycle_solved.m_recomp_frac);		//[-]
		assign("P_comp_in",sco2_recomp_csp.get_design_solved()->ms_rc_cycle_solved.m_pres[1-1]/1000.0);		//[MPa] convert from kPa
		assign("P_comp_out",sco2_recomp_csp.get_design_solved()->ms_rc_cycle_solved.m_pres[2-1]/1000.0);	//[MPa] convert from kPa
			// PHX
		assign("UA_PHX",sco2_recomp_csp.get_design_solved()->ms_phx_des_solved.m_UA_design_total);			//[kW/K]
		assign("eff_PHX",sco2_recomp_csp.get_design_solved()->ms_phx_des_solved.m_eff_design);				//[-]
		assign("NTU_PHX",sco2_recomp_csp.get_design_solved()->ms_phx_des_solved.m_NTU_design);				//[-]

		// Set up off-design analysis
		bool is_m_dot_fracs = as_boolean("is_m_dot_htf_fracs");
		bool is_T_amb_od = as_boolean("is_T_amb_od");

		size_t n_m_dot_fracs = 1;
		size_t n_T_amb_od = 1;

		std::vector<double> m_dot_htf_fracs;
		std::vector<double> T_amb_od;

		if( is_m_dot_fracs )
		{
			ssc_number_t *p_m_dot_htf_fracs = as_array("m_dot_htf_fracs_in", &n_m_dot_fracs);
			m_dot_htf_fracs.resize(n_m_dot_fracs);
			for( int i = 0; i < n_m_dot_fracs; i++ )
				m_dot_htf_fracs[i] = (double) p_m_dot_htf_fracs[i];
		}
		else
		{
			m_dot_htf_fracs.resize(1);
			m_dot_htf_fracs[0] = 1.0;		//[-]
		}
		
		if( is_T_amb_od )
		{
			ssc_number_t *p_T_amb_od = as_array("T_amb_od_in", &n_T_amb_od);
			T_amb_od.resize(n_T_amb_od);
			for( int i = 0; i < n_T_amb_od; i++ )
				T_amb_od[i] = (double) p_T_amb_od[i];
		}
		else
		{
			T_amb_od.resize(1);
			T_amb_od[0] = as_double("T_amb_des");	//[C]
		}

		int n_od_runs = n_m_dot_fracs*n_T_amb_od;
			// Off-design parameters
		ssc_number_t *p_m_dot_htf_fracs = allocate("m_dot_htf_fracs", n_od_runs);
		ssc_number_t *p_T_amb_od = allocate("T_amb_od", n_od_runs);
		ssc_number_t *p_T_htf_hot_od = allocate("T_htf_hot_od", n_od_runs);
			// Optimized control parameters
		ssc_number_t *p_P_comp_in_od = allocate("P_comp_in_od", n_od_runs);
		ssc_number_t *p_N_mc_od = allocate("N_mc_od", n_od_runs);
		ssc_number_t *p_recomp_frac_od = allocate("recomp_frac_od", n_od_runs);			
			// Results
		ssc_number_t *p_eta_thermal_od = allocate("eta_thermal_od", n_od_runs);

		for(int n_run = 0; n_run < n_od_runs; n_run++)
		{
			// Setup off-design analysis for 'n_run'
			int i_m_dot_htf = n_run / n_T_amb_od;
			int j_T_amb_od = n_run % n_T_amb_od;

			double m_dot_htf_od_run = m_dot_htf_fracs[i_m_dot_htf];		//[-]
			double T_amb_od_run = T_amb_od[j_T_amb_od];					//[C]
			double T_htf_od_run = as_double("T_htf_hot_des");			//[C]

			p_m_dot_htf_fracs[n_run] = m_dot_htf_od_run;	//[-]
			p_T_amb_od[n_run] = T_amb_od_run;				//[-]
			p_T_htf_hot_od[n_run] = T_htf_od_run;			//[C]
			
			// Try calling off-design model with design parameters
			C_sco2_recomp_csp::S_od_par sco2_rc_od_par;
			sco2_rc_od_par.m_T_htf_hot = T_htf_od_run + 273.15;		//[K]
			sco2_rc_od_par.m_m_dot_htf = m_dot_htf_design*m_dot_htf_od_run;	//[kg/s]
			sco2_rc_od_par.m_T_amb = T_amb_od_run + 273.15;			//[K]
			int od_strategy = C_sco2_recomp_csp::FIX_T_MC_APPROACH__FLOAT_PHX_DT;

			int off_design_code = 0;
			try
			{
				off_design_code = sco2_recomp_csp.off_design(sco2_rc_od_par, od_strategy);
			}
			catch( C_csp_exception &csp_exception )
			{
				// Report warning before exiting with error
				while( sco2_recomp_csp.mc_messages.get_message(&out_type, &out_msg) )
				{
					log(out_msg);
				}

				log(csp_exception.m_error_message, SSC_ERROR, -1.0);

				return;
			}

			if(off_design_code == 0)
			{	// Off-design call was successful, so write outputs
					// Control parameters
				p_P_comp_in_od[n_run] = sco2_recomp_csp.get_od_solved()->ms_rc_cycle_od_solved.m_pres[1-1]/1000.0;	//[MPa]
				p_N_mc_od[n_run] = sco2_recomp_csp.get_od_solved()->ms_rc_cycle_od_solved.ms_mc_od_solved.m_N;		//[rpm]
				p_recomp_frac_od[n_run] = sco2_recomp_csp.get_od_solved()->ms_rc_cycle_od_solved.m_recomp_frac;		//[-]
					// Results
				p_eta_thermal_od[n_run] = sco2_recomp_csp.get_od_solved()->ms_rc_cycle_od_solved.m_eta_thermal;
			}
			else
			{	// Off-design call failed, write NaN outptus
					// Control parameters
				p_P_comp_in_od[n_run] = std::numeric_limits<double>::quiet_NaN();
				p_N_mc_od[n_run] = std::numeric_limits<double>::quiet_NaN();
				p_recomp_frac_od[n_run] = std::numeric_limits<double>::quiet_NaN();
					// Results
				p_eta_thermal_od[n_run] = std::numeric_limits<double>::quiet_NaN();
			}

		}

		// If all calls were successful, log to SSC any messages from sco2_recomp_csp
		while( sco2_recomp_csp.mc_messages.get_message(&out_type, &out_msg) )
		{
			log(out_msg);
		}
		
	}

};

DEFINE_MODULE_ENTRY(sco2_csp_system, "...", 0)