#include <gmock/gmock.h>
#include <memory>

#include "smart_home.h"

class SmartHomeControllerTest : public ::testing::Test {
protected:
    SmartHomeControllerTest() { controller = std::make_unique<SmartHomeController>(); }
    std::unique_ptr<SmartHomeController> controller;
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
    std::string expected = "Dimmable light dimmed to 50%";

    EXPECT_EQ(controller->dimmable_light.dim(50), expected);
}

TEST_F(SmartHomeControllerTest, ConnectLightToNetwork)
{
    std::string expected = "Networkable light connected to Home Network";

    EXPECT_EQ(controller->networkable_light.connect_to_network("Home Network"), expected);
}

TEST_F(SmartHomeControllerTest, BlindsOpen)
{
    std::string expected = "Blinds open";

    EXPECT_EQ(controller->blinds.open(), expected);
}

TEST_F(SmartHomeControllerTest, MakeQuickBreakfast)
{
    std::vector<std::string> expected = {
        "Blinds open",
        "Coffee maker turned on",
        "Brewing Colombian coffee",
        "Coffee maker turned off",
    };

    EXPECT_EQ(controller->make_quick_breakfast("Colombian"), expected);
}

TEST_F(SmartHomeControllerTest, VacuumCleanerStartCleaning)
{
    std::string expected = "Vacuum cleaner started cleaning";

    EXPECT_EQ(controller->vacuum_cleaner.start_cleaning(), expected);
}

TEST_F(SmartHomeControllerTest, VacuumCleanerStopCleaning)
{
    std::string expected = "Vacuum cleaner stopped cleaning";

    EXPECT_EQ(controller->vacuum_cleaner.stop_cleaning(), expected);
}

TEST_F(SmartHomeControllerTest, ScheduleNightCleaning)
{
    std::vector<std::string> expected_shedule_cleaning = {
        "Night cleaning sheduled",
    };
    std::vector<std::string> expected_turn_off = {
        "Switchable light turned off",
        "Switchable light turned off",
        "Networkable light turned off",
        "Dimmable light turned off",
        "Coffee maker turned off",
        "AC turned off",
        "Vacuum cleaner started cleaning",
    };

    EXPECT_EQ(controller->schedule_night_cleaning(), expected_shedule_cleaning);
    EXPECT_EQ(controller->turn_off_all(), expected_turn_off);
}
