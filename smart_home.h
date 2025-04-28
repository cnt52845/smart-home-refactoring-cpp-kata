#pragma once

#include <iostream>
#include <string>
#include <vector>

class SwitchableLight {
public:
    std::string turn_on() { return "Switchable light turned on"; }
    std::string turn_off() { return "Switchable light turned off"; }
};

class DimmableLight {
public:
    std::string turn_on() { return "Dimmable light turned on at full brightness"; }
    std::string turn_off() { return "Dimmable light turned off"; }

    std::string dim(int level_in_percent)
    {
        return "Dimmable light dimmed to " + std::to_string(level_in_percent) + "%";
    }
};

class NetworkableLight {
public:
    std::string turn_on() { return "Networkable light turned on"; }
    std::string turn_off() { return "Networkable light turned off"; }

    std::string connect_to_network(const std::string& network_name)
    {
        return "Networkable light connected to " + network_name;
    }
};

class AirConditioner {
public:
    std::string turn_on() { return "AC turned on"; }
    std::string turn_off() { return "AC turned off"; }

    std::string set_temperature(int temperature_in_celcius)
    {
        return "Set temperature to " + std::to_string(temperature_in_celcius);
    }
};

class CoffeeMaker {
public:
    std::string turn_on() { return "Coffee maker turned on"; }
    std::string turn_off() { return "Coffee maker turned off"; }

    std::string brew(const std::string& coffee_type)
    {
        return "Brewing " + coffee_type + " coffee";
    }
};

class SmartHomeController {
public:
    std::vector<std::string> turn_on_all()
    {
        return {
            switchable_light_1->turn_on(),
            switchable_light_2->turn_on(),
            networkable_light->turn_on(),
            dimmable_light->turn_on(),
            coffee_maker->turn_on(),
            ac->turn_on(),
        };
    }

    std::vector<std::string> turn_off_all()
    {
        return {
            switchable_light_1->turn_off(),
            switchable_light_2->turn_off(),
            networkable_light->turn_off(),
            dimmable_light->turn_off(),
            coffee_maker->turn_off(),
            ac->turn_off(),
        };
    }

private:
    std::shared_ptr<SwitchableLight>  switchable_light_1{std::make_shared<SwitchableLight>()};
    std::shared_ptr<SwitchableLight>  switchable_light_2{std::make_shared<SwitchableLight>()};
    std::shared_ptr<NetworkableLight> networkable_light{std::make_shared<NetworkableLight>()};
    std::shared_ptr<DimmableLight>    dimmable_light{std::make_shared<DimmableLight>()};
    std::shared_ptr<CoffeeMaker>      coffee_maker{std::make_shared<CoffeeMaker>()};
    std::shared_ptr<AirConditioner>   ac{std::make_shared<AirConditioner>()};
};
