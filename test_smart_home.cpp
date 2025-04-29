#include <gmock/gmock.h>
#include <memory>

#include "smart_home.h"

class SmartHomeControllerTest : public ::testing::Test {
protected:
    void SetUp() override
    {
        controller->add_device(std::make_shared<SwitchableLight>("Living Room Light"));
        controller->add_device(std::make_shared<SwitchableLight>("Dining Room Light"));
        controller->add_device(std::make_shared<NetworkableLight>("Kitchen Light"));
        controller->add_device(std::make_shared<DimmableLight>("Bedroom Light"));
        controller->add_device(std::make_shared<CoffeeMaker>("Coffee Maker"));
        controller->add_device(std::make_shared<AirConditioner>("AC"));
        controller->add_device(std::make_shared<Blinds>("Bedroom Blinds"));
        controller->add_device(std::make_shared<VacuumCleaner>("Vacuum Cleaner"));
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
    std::shared_ptr<DimmableLight> dimmable_light{
        std::make_shared<DimmableLight>("Dimmable Light")};
    std::string expected = "Dimmable light dimmed to 50%";

    EXPECT_EQ(dimmable_light->dim(50), expected);
}

TEST_F(SmartHomeControllerTest, ConnectLightToNetwork)
{
    std::shared_ptr<NetworkableLight> networkable_light{
        std::make_shared<NetworkableLight>("Networkable Light")};
    std::string expected = "Networkable light connected to Home Network";

    EXPECT_EQ(networkable_light->connect_to_network("Home Network"), expected);
}

TEST_F(SmartHomeControllerTest, MakeQuickBreakfast)
{
    std::vector<std::string> expected = {
        "Blinds opened",
        "Coffee maker turned on",
        "Brewing Colombian coffee",
        "Coffee maker turned off",
    };

    EXPECT_EQ(controller->make_quick_breakfast("Bedroom Blinds", "Coffee Maker", "Colombian"),
              expected);
}

TEST_F(SmartHomeControllerTest, ScheduleNightCleaning)
{
    std::vector<std::string> expected_schedule_cleaning_output = {
        "Night cleaning scheduled",
    };
    std::vector<std::string> expected_turn_off_output = {
        "Switchable light turned off",
        "Switchable light turned off",
        "Networkable light turned off",
        "Dimmable light turned off",
        "Coffee maker turned off",
        "AC turned off",
        "Vacuum cleaner started cleaning",
    };

    EXPECT_EQ(controller->schedule_night_cleaning("Vacuum Cleaner"),
              expected_schedule_cleaning_output);
    EXPECT_EQ(controller->turn_off_all(), expected_turn_off_output);
}
