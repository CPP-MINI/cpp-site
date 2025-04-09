#include <cstdlib>
#include <iostream>
#include <fstream>
#include <getopt.h>

#include "decoder.hpp"
#include "encoder.hpp"


struct settings {
    int decode;
    std::string input_file;
};

settings parse_args(int argc, char *argv[])
{
    settings settings{};
    char c;

    while (1)
    {
        static struct option long_options[] =
        {
            {"decode", no_argument, &settings.decode, 1},
            {0, 0, 0, 0}
        };
        /* getopt_long stores the option index here. */
        int option_index = 0;

        c = getopt_long(argc, argv, "d",
                        long_options, &option_index);

        /* Detect the end of the options. */
        if (c == -1)
            break;

        switch (c)
        {
            case 0:
                /* If this option set a flag, do nothing else now. */
                if (long_options[option_index].flag != 0)
                    break;
            break;
            case 'd':
                settings.decode = 1;
            break;
            case '?':
                /* getopt_long already printed an error message. */
                    break;
            default:
                abort();
        }
    }

    for (; optind < argc; optind++)
    {
        if (argv[optind][0] != '-')
            settings.input_file = argv[optind];
    }

    return settings;
}

using namespace l4;

int main(int argc, char *argv[])
{
    auto settings = parse_args(argc, argv);

    std::istream* input_stream = &std::cin;
    std::ifstream file_input;
    if (!settings.input_file.empty())
    {
        file_input = std::ifstream(settings.input_file);
        input_stream = &file_input;
    }

    std::string s(std::istreambuf_iterator<std::istream::char_type>(*input_stream), {});

    if (settings.decode)
    {
        base32::Decoder dec(s);
        auto bytestream = dec.pullBytestream();
        std::cout.write(reinterpret_cast<const std::ostream::char_type *>(bytestream.data()), bytestream.size());
        std::cout << std::endl;
    }
    else
    {
        base32::Encoder encoder;
        encoder.pushBytes(reinterpret_cast<const std::byte *>(s.data()), s.size());
        std::cout << encoder.encodedString();
    }

    return EXIT_SUCCESS;
}
