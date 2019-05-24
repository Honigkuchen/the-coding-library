// STL includes
#include <iostream>
#include <chrono>

// Project includes
#include <huffman.h>

int main()
{
//    std::vector<char> message = {'a', 'b', 'c', 'a', 'd', 'e', 'd'};
    std::string s = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nullam justo enim, cursus nec diam a, hendrerit ultricies mauris. Nullam porta turpis vestibulum accumsan faucibus. Pellentesque sit amet dictum risus, vitae faucibus felis. Quisque mi diam, maximus ut semper eget, auctor sit amet lectus. Sed gravida lectus purus, eu pulvinar orci ultrices vitae. Integer dictum posuere vulputate. Ut vitae ipsum lacinia, semper nisl eu, tristique erat.";
    std::vector<char> message(s.begin(), s.end());

    auto start = std::chrono::system_clock::now();
    huffman::Table<char> table = huffman::Encode(message);
    auto end = std::chrono::system_clock::now();

    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    auto a_binary_number = table['s'];

    std::cout << a_binary_number;
    std::cout << std::endl;

    std::cout << "Duration: " << elapsed.count() << "ns" << std::endl;

    return 0;
}
