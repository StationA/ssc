#ifndef _CMOD_BATTERY_COMMON_
#define _CMOD_BATTERY_COMMON_ 1

#include "core.h"
#include "lib_battery.h"


extern var_info vtab_battery[];

struct battstor
{

	battstor( compute_module &cm, bool setup_model, int replacement_option, size_t nrec, double dt_hr );
	void initialize_automated_dispatch(ssc_number_t *pv=0, ssc_number_t *load=0, int mode=0);
	~battstor();

	// Note, PV & LOAD are energy quantities, not power
	void advance( compute_module &cm, size_t idx, size_t hour_of_year, size_t step, size_t year, double PV, double LOAD );
	void update_post_inverted(compute_module &cm, size_t idx, double PV, double LOAD);

	// for user schedule
	void force_replacement();
	void check_replacement_schedule(int batt_replacement_option, size_t count_batt_replacement, ssc_number_t *batt_replacement, int iyear, int hour, int step);


	void calculate_monthly_and_annual_outputs( compute_module &cm );


	// time quantities
	int year;
	size_t step_per_hour;
	size_t nyears;
	double _dt_hour;

	// member data
	voltage_dynamic_t *voltage_model;
	lifetime_t *lifetime_model;
	thermal_t *thermal_model;
	capacity_t *capacity_model;
	battery_t *battery_model;
	dispatch_manual_t *dispatch_model;
	automate_dispatch_t *automated_dispatch;
	losses_t *losses_model;

	bool en;
	int chem;
	

	int batt_dispatch;
	bool dm_charge[6], dm_discharge[6], dm_gridcharge[6]; // manual dispatch
	std::map<int, double> dm_percent_discharge; // <profile, discharge_percent>
	std::map<int, double> dm_percent_gridcharge; // <profile, gridcharge_percent>
	util::matrix_t<float> dm_dynamic_sched;
	
	bool ac_or_dc;
	double dc_dc, ac_dc, dc_ac;

	double e_charge;
	double e_discharge;

	double * pv_prediction;
	double * load_prediction;
	int prediction_index;

	// outputs
	ssc_number_t
		*outTotalCharge,
		*outAvailableCharge,
		*outBoundCharge,
		*outMaxChargeAtCurrent,
		*outMaxCharge,
		*outSOC,
		*outDOD,
		*outCurrent,
		*outCellVoltage,
		*outBatteryVoltage,
		*outCapacityPercent,
		*outCycles,
		*outBatteryBankReplacement,
		*outBatteryTemperature,
		*outCapacityThermalPercent,
		*outDispatchMode,
		*outBatteryPower,
		*outGridPower,
		*outGenPower,
		*outPVToLoad,
		*outBatteryToLoad,
		*outGridToLoad,
		*outAnnualChargeEnergy,
		*outAnnualDischargeEnergy,
		*outAnnualGridImportEnergy,
		*outAnnualGridExportEnergy,
		*outAnnualEnergyLoss;


	double outAverageCycleEfficiency;
};


#endif
