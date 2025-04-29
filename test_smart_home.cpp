#include <gmock/gmock.h>
#include <memory>

#include "smart_home.h"

class SmartHomeControllerTest : public ::testing::Test {
protected:
    void SetUp() override
    {
        controller->add_device(std::make_shared<SwitchableLight>());
        controller->add_device(std::make_shared<SwitchableLight>());
        controller->add_device(std::make_shared<NetworkableLight>());
        controller->add_device(std::make_shared<DimmableLight>());
        controller->add_device(std::make_shared<CoffeeMaker>());
        controller->add_device(std::make_shared<AirConditioner>());
    }

    std::unique_ptr<SmartHomeController> controller{std::make_unique<SmartHomeController>()};
};

TEST_F(SmartHomeControllerTest, TurnOnAll)
{
    std::vector<std::string> expected = {
        "Switchable light turned on",
        "Switchable light turned on",
        "Networkable light turned on",
        "Dimmable light turned on at full brightness",
        "Coffee maker turned on",
        "AC turned on",
    };

    EXPECT_EQ(controller->turn_on_all(), expected);
}

TEST_F(SmartHomeControllerTest, TurnOffAll)
{
    std::vector<std::string> expected = {
        "Switchable light turned off",
        "Switchable light turned off",
        "Networkable light turned off",
        "Dimmable light turned off",
        "Coffee maker turned off",
        "AC turned off",
    };

    EXPECT_EQ(controller->turn_off_all(), expected);
}

TEST_F(SmartHomeControllerTest, DimLight)
{
    std::shared_ptr<DimmableLight> dimmable_light{std::make_shared<DimmableLight>()};
    std::string                    expected = "Dimmable light dimmed to 50%";

    EXPECT_EQ(dimmable_light->dim(50), expected);
}

TEST_F(SmartHomeControllerTest, ConnectLightToNetwork)
{
    std::shared_ptr<NetworkableLight> networkable_light{std::make_shared<NetworkableLight>()};
    std::string                       expected = "Networkable light connected to Home Network";

    EXPECT_EQ(networkable_light->connect_to_network("Home Network"), expected);
}
