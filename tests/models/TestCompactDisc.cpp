#include <gtest/gtest.h>
#include "../../includes/models/CompactDisc.h"

namespace MusicSalon {
namespace Tests {

class CompactDiscTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Создаём тестовый компакт-диск для всех тестов
        fullDisc = std::make_unique<Models::CompactDisc>(
            1, "Test Album", "2023-01-01", "Test Producer", 15.99,
            "2023-01-02", "2023-01-02", 1);
        
        newDisc = std::make_unique<Models::CompactDisc>(
            "New Album", "2023-02-01", "New Producer", 19.99);
    }
    
    void TearDown() override {
        fullDisc.reset();
        newDisc.reset();
    }
    
    std::unique_ptr<Models::CompactDisc> fullDisc;
    std::unique_ptr<Models::CompactDisc> newDisc;
};

TEST_F(CompactDiscTest, ConstructorWithFullParamsInitializesAllFields) {
    ASSERT_EQ(fullDisc->getDiscCode(), 1);
    ASSERT_EQ(fullDisc->getTitle(), "Test Album");
    ASSERT_EQ(fullDisc->getManufactureDate(), "2023-01-01");
    ASSERT_EQ(fullDisc->getProducer(), "Test Producer");
    ASSERT_DOUBLE_EQ(fullDisc->getPrice(), 15.99);
    ASSERT_EQ(fullDisc->getCreateDate(), "2023-01-02");
    ASSERT_EQ(fullDisc->getLastUpdate(), "2023-01-02");
    ASSERT_EQ(fullDisc->getCreatedBy(), 1);
}

TEST_F(CompactDiscTest, ConstructorWithoutIdInitializesBasicFields) {
    ASSERT_EQ(newDisc->getDiscCode(), -1);  // Ожидаем -1 для нового диска без ID
    ASSERT_EQ(newDisc->getTitle(), "New Album");
    ASSERT_EQ(newDisc->getManufactureDate(), "2023-02-01");
    ASSERT_EQ(newDisc->getProducer(), "New Producer");
    ASSERT_DOUBLE_EQ(newDisc->getPrice(), 19.99);
    ASSERT_TRUE(newDisc->getCreateDate().empty());
    ASSERT_TRUE(newDisc->getLastUpdate().empty());
    ASSERT_EQ(newDisc->getCreatedBy(), -1);
}

TEST_F(CompactDiscTest, SettersChangeFieldValues) {
    fullDisc->setTitle("Updated Title");
    fullDisc->setManufactureDate("2023-03-01");
    fullDisc->setProducer("Updated Producer");
    fullDisc->setPrice(24.99);
    fullDisc->setLastUpdate("2023-03-02");
    
    ASSERT_EQ(fullDisc->getTitle(), "Updated Title");
    ASSERT_EQ(fullDisc->getManufactureDate(), "2023-03-01");
    ASSERT_EQ(fullDisc->getProducer(), "Updated Producer");
    ASSERT_DOUBLE_EQ(fullDisc->getPrice(), 24.99);
    ASSERT_EQ(fullDisc->getLastUpdate(), "2023-03-02");
}

} // namespace Tests
} // namespace MusicSalon
