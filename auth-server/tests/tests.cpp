#include "mock_classes.h"

// TEST(MockRequestsHandler, RequestHandlerTest) {
//     ASSERT_TRUE(true);
//     MockRequestsHandler handler;

//     EXPECT_CALL(handler, getResponse).Times(testing::AtLeast(1));
// }

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
