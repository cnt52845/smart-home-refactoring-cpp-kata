#pragma once

#include <iostream>
#include <string>
#include <vector>

class Device {
public:
    virtual ~Device() = default;
};

class Switchable {
public:
    virtual ~Switchable()          = default;
    virtual std::string turn_on()  = 0;
    virtual std::string turn_off() = 0;
};

class Dimmable {
public:
    virtual ~Dimmable()                           = default;
    virtual std::string dim(int level_in_percent) = 0;
};

class Networkable {
public:
    virtual ~Networkable()                                                  = default;
    virtual std::string connect_to_network(const std::string& network_name) = 0;
};

class TemperatureAdjustable {
public:
    virtual ~TemperatureAdjustable()                                = default;
    virtual std::string set_temperature(int temperature_in_celcius) = 0;
};

class BeverageMaker {
public:
    virtual ~BeverageMaker()                                   = default;
    virtual std::string brew(const std::string& beverage_type) = 0;
};

class SwitchableLight final : public Device, public Switchable {
public:
    std::string turn_on() override { return "Switchable light turned on"; }
    std::string turn_off() override { return "Switchable light turned off"; }
};

class DimmableLight final : public Device, public Switchable, public Dimmable {
public:
    std::string turn_on() override { return "Dimmable light turned on at full brightness"; }
    std::string turn_off() override { return "Dimmable light turned off"; }

    std::string dim(int level_in_percent) override
    {
        return "Dimmable light dimmed to " + std::to_string(level_in_percent) + "%";
    }
};

class NetworkableLight final : public Device, public Switchable, public Networkable {
public:
    std::string turn_on() override { return "Networkable light turned on"; }
    std::string turn_off() override { return "Networkable light turned off"; }

    std::string connect_to_network(const std::string& network_name) override
    {
        return "Networkable light connected to " + network_name;
    }
};

class AirConditioner final : public Device, public Switchable, public TemperatureAdjustable {
public:
    std::string turn_on() override { return "AC turned on"; }
    std::string turn_off() override { return "AC turned off"; }

    std::string set_temperature(int temperature_in_celcius) override
    {
        return "Set temperature to " + std::to_string(temperature_in_celcius);
    }
};

class CoffeeMaker final : public Device, public Switchable, public BeverageMaker {
public:
    std::string turn_on() override { return "Coffee maker turned on"; }
    std::string turn_off() override { return "Coffee maker turned off"; }

    std::string brew(const std::string& coffee_type) override
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
