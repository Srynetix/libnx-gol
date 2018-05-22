import argparse
import math


def main():
    parser = argparse.ArgumentParser(description="font tool")
    parser.add_argument("binary")

    args = parser.parse_args()
    hex_str = generate_hex(args.binary)

    print(hex_str)


def generate_hex(binary):
    flat = "".join(binary.split(" "))
    packets = partition_str(flat, 4)
    rev_packets = reverse_all(packets)
    hex_str = ""

    for p in rev_packets:
        hex_str += hex(int(p, base=2))[2:]
    hex_str = "0x{0}".format(hex_str)

    return hex_str


def partition_str(s, limit):
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
    output = []
    for x in l[::-1]:
        output.append("".join(list(reversed(x))))

    return output


if __name__ == "__main__":
    main()
