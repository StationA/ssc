#ifndef __ssc_eqn_h
#define __ssc_eqn_h

#include <ssc/sscapi.h>
#include <ssc/cmod_windpower_eqns.h>

typedef void (*ssc_equation_ptr)(ssc_data_t data);

struct ssc_equation_entry{
    const char* name;
    ssc_equation_ptr func;
    const char* cmod;
    const char* doc;
};

static ssc_equation_entry ssc_equation_table [] = {
        {"WindTurbine_calculate_powercurve", WindTurbine_calculate_powercurve,
                           "Windpower", WindTurbine_calculate_powercurve_doc},
        {nullptr, nullptr, nullptr, nullptr}
};

#endif