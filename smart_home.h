#pragma once

#include <iostream>
#include <string>
#include <vector>

// Abtract interfaces
class Device {
public:
    explicit Device(std::string device_name) : name(std::move(device_name)) {}
    virtual ~Device() = default;

    const std::string& get_name() const { return name; }

private:
    std::string name;
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

class ShadeControl {
public:
    virtual ~ShadeControl()     = default;
    virtual std::string open()  = 0;
    virtual std::string close() = 0;
};

class CleaningAppliance {
public:
    virtual ~CleaningAppliance()         = default;
    virtual std::string start_cleaning() = 0;
    virtual std::string stop_cleaning()  = 0;
};

// Concreete devices implementing the interfaces
class SwitchableLight final : public Device, public Switchable {
public:
    explicit SwitchableLight(std::string device_name) : Device(std::move(device_name)) {}

    std::string turn_on() override { return "Switchable light turned on"; }
    std::string turn_off() override { return "Switchable light turned off"; }
};

class DimmableLight final : public Device, public Switchable, public Dimmable {
public:
    explicit DimmableLight(std::string device_name) : Device(std::move(device_name)) {}

    std::string turn_on() override { return "Dimmable light turned on at full brightness"; }
    std::string turn_off() override { return "Dimmable light turned off"; }

    std::string dim(int level_in_percent) override
    {
        return "Dimmable light dimmed to " + std::to_string(level_in_percent) + "%";
    }
};

class NetworkableLight final : public Device, public Switchable, public Networkable {
public:
    explicit NetworkableLight(std::string device_name) : Device(std::move(device_name)) {}

    std::string turn_on() override { return "Networkable light turned on"; }
    std::string turn_off() override { return "Networkable light turned off"; }

    std::string connect_to_network(const std::string& network_name) override
    {
        return "Networkable light connected to " + network_name;
    }
};

class AirConditioner final : public Device, public Switchable, public TemperatureAdjustable {
public:
    explicit AirConditioner(std::string device_name) : Device(std::move(device_name)) {}

    std::string turn_on() override { return "AC turned on"; }
    std::string turn_off() override { return "AC turned off"; }

    std::string set_temperature(int temperature_in_celcius) override
    {
        return "Set temperature to " + std::to_string(temperature_in_celcius);
    }
};

class CoffeeMaker final : public Device, public Switchable, public BeverageMaker {
public:
    explicit CoffeeMaker(std::string device_name) : Device(std::move(device_name)) {}

    std::string turn_on() override { return "Coffee maker turned on"; }
    std::string turn_off() override { return "Coffee maker turned off"; }

    std::string brew(const std::string& coffee_type) override
    {
        return "Brewing " + coffee_type + " coffee";
    }
};

class Blinds final : public Device, public ShadeControl {
public:
    explicit Blinds(std::string device_name) : Device(std::move(device_name)) {}

    std::string open() override { return "Blinds opened"; }
    std::string close() override { return "Blinds closed"; }
};

class VacuumCleaner final : public Device, public CleaningAppliance {
public:
    explicit VacuumCleaner(std::string device_name) : Device(std::move(device_name)) {}

    std::string start_cleaning() override { return "Vacuum cleaner started cleaning"; }
    std::string stop_cleaning() override { return "Vacuum cleaner stopped cleaning"; }
};

// Main controller class
class SmartHomeController {
public:
    void add_device(std::shared_ptr<Device> device) { devices.push_back(device); }

    std::vector<std::string> turn_on_all()
    {
        std::vector<std::string> result;
        for (const auto& device : devices) {
            if (auto switchable = std::dynamic_pointer_cast<Switchable>(device)) {
                result.push_back(switchable->turn_on());
            }
        }
        return result;
    }

    std::vector<std::string> turn_off_all()
    {
        std::vector<std::string> result;
        for (const auto& device : devices) {
            if (auto switchable = std::dynamic_pointer_cast<Switchable>(device)) {
                result.push_back(switchable->turn_off());
            }
        }
        return result;
    }

    std::vector<std::string> make_quick_breakfast(const std::string& blinds_name,
                                                  const std::string& coffe_maker_name,
                                                  const std::string& coffee_type)
    {
        std::vector<std::string> result;

        auto blinds = std::dynamic_pointer_cast<Blinds>(find_device(blinds_name));
        if (blinds) {
            result.push_back(blinds->open());
        }

        auto coffee_maker = std::dynamic_pointer_cast<CoffeeMaker>(find_device(coffe_maker_name));
        if (coffee_maker) {
            result.push_back(coffee_maker->turn_on());
            result.push_back(coffee_maker->brew(coffee_type));
            result.push_back(coffee_maker->turn_off());
        }

        return result;
    }

private:
    const std::shared_ptr<Device> find_device(const std::string& device_name)
    {
        auto it = std::find_if(devices.begin(), devices.end(), [&device_name](const auto& device) {
            return device->get_name() == device_name;
        });
        return (it != devices.end()) ? *it : nullptr;
    }

    std::vector<std::shared_ptr<Device>> devices;
};
