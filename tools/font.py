"""
Hex font data generator.

From an input string, generate an 32-bit hex code to use for font rendering.

Example, for a font size of 5 x 6 pixels (0 for a white pixel and 1 for a black pixel)

..o..  =>  00100
.ooo.  =>  01110
..o..  =>  00100
..o..  =>  00100
.ooo.  =>  01110
..o..  =>  00100

=> Input string: "00100 01110 00100 00100 01110 00100"
=> Hex code: 0x08e211c4
"""

import argparse
import math


def main():
    parser = argparse.ArgumentParser(description="hex font data generator")
    parser.add_argument("binary")

    args = parser.parse_args()
    hex_str = generate_hex(args.binary)

    print(hex_str)


def generate_hex(binary):
    """
    Generate hex string from binary string.

    String format (5 * 6):
        "00000 00000 00000 00000 00000 00000"

    :param binary:  Binary string (str)
    :rtype: Hex string (str)
    """
    flat = "".join(binary.split(" "))
    packets = partition_str(flat, 4)
    rev_packets = reverse_all(packets)
    hex_str = ""

    for p in rev_packets:
        hex_str += hex(int(p, base=2))[2:]
    hex_str = "0x{0}".format(hex_str)

    return hex_str


def partition_str(s, limit):
    """
    Partition string each `limit` character.

    Example:
        s: "foobarfoobarfoobar"
        limit: 4
        result: ["foob", "arfo", "obar", "foob", "ar"]

    :param s:       String (str)
    :param limit:   Limit (int)
    :rtype: List (list)
    """
    str_length = len(s)

    output = []
    current = []

    packs_len = int(math.ceil(str_length / limit))
    for l in range(packs_len):
        for i in range(limit):
            idx = i + l * limit
            if idx < str_length:
                current.append(s[idx])

        output.append("".join(current))
        current = []

    return output


def reverse_all(l):
    """
    Reverse a list, while reversing its content.

    Example:
        l: ["abcde", "fghij"]
        result: ["jihgf", "edcba"]

    :param l:   List (list)
    :rtype: Reversed list (list)
    """
    output = []
    for x in l[::-1]:
        output.append("".join(list(reversed(x))))

    return output


if __name__ == "__main__":
    main()
