clang++ -x objective-c++ -framework IOKit -framework CoreFoundation -lopencv_core -lopencv_imgcodecs wrapper/MyObject.mm wrapper/MyCPPWrapper.cpp main.cpp -o app.out
./app.out
