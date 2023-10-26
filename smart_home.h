#pragma once

#include <iostream>
#include <string>
#include <vector>

struct SwitchableLight {
    std::string turn_on() { return "Switchable light turned on"; }
    std::string turn_off() { return "Switchable light turned off"; }
};

struct DimmableLight {
    std::string turn_on() { return "Dimmable light turned on at full brightness"; }
    std::string turn_off() { return "Dimmable light turned off"; }

    std::string dim(int level_in_percent)
    {
        return "Dimmable light dimmed to " + std::to_string(level_in_percent) + "%";
    }
};

struct NetworkableLight {
    std::string turn_on() { return "Networkable light turned on"; }
    std::string turn_off() { return "Networkable light turned off"; }

    std::string connect_to_network(const std::string& network_name)
    {
        return "Networkable light connected to " + network_name;
    }
};

struct AirConditioner {
    std::string turn_on() { return "AC turned on"; }
    std::string turn_off() { return "AC turned off"; }

    std::string set_temperature(int temperature_in_celcius)
    {
        return "Set temperature to " + std::to_string(temperature_in_celcius);
    }
};

struct CoffeeMaker {
    std::string turn_on() { return "Coffee maker turned on"; }
    std::string turn_off() { return "Coffee maker turned off"; }

    std::string brew(const std::string& coffee_type)
    {
        return "Brewing " + coffee_type + " coffee";
    }
};

struct Blinds {
    std::string open() { return "Blinds open"; }
    std::string close() { return "Blinds closed"; }
};

struct VacuumCleaner {
    std::string start_cleaning() { return "Vacuum cleaner started cleaning"; }
    std::string stop_cleaning() { return "Vacuum cleaner stopped cleaning"; }
};

struct SmartHomeController {
    std::vector<std::string> turn_on_all()
    {
        return {
            switchable_light_1.turn_on(),
            switchable_light_2.turn_on(),
            networkable_light.turn_on(),
            dimmable_light.turn_on(),
            coffee_maker.turn_on(),
            ac.turn_on(),
        };
    }

    std::vector<std::string> turn_off_all()
    {
        std::vector<std::string> result{
            switchable_light_1.turn_off(),
            switchable_light_2.turn_off(),
            networkable_light.turn_off(),
            dimmable_light.turn_off(),
            coffee_maker.turn_off(),
            ac.turn_off(),
        };
        if (is_night_cleaning_scheduled) {
            std::cout << "before emplace" << std::endl;
            result.emplace_back(vacuum_cleaner.start_cleaning());
        }
        return result;
    }

    std::vector<std::string> make_quick_breakfast(const std::string& coffee_type)
    {
        return {
            blinds.open(),
            coffee_maker.turn_on(),
            coffee_maker.brew(coffee_type),
            coffee_maker.turn_off(),
        };
    }

    std::vector<std::string> schedule_night_cleaning()
    {
        is_night_cleaning_scheduled = true;
        return {"Night cleaning sheduled"};
    }

    SwitchableLight  switchable_light_1;
    SwitchableLight  switchable_light_2;
    NetworkableLight networkable_light;
    DimmableLight    dimmable_light;
    CoffeeMaker      coffee_maker;
    AirConditioner   ac;
    Blinds           blinds;
    VacuumCleaner    vacuum_cleaner;
    bool             is_night_cleaning_scheduled{false};
};
