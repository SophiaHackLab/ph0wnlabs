#!/usr/bin/env python
    
import sys

def string_to_ascii_binary(data_string):
    """Converts a string to binary (8 bits per character)"""
    return ''.join(format(ord(c), '08b') for c in data_string)

def generate_fake_qr(data_string):
    """Generates the fake ASCII QR code"""
    binary_data = string_to_ascii_binary(data_string)
    fake_qr = []

    # Break the binary data into chunks of 8 bits and convert to fake QR lines
    for i in range(0, len(binary_data), 8):
        line = binary_data[i:i+8]
        fake_qr.append(''.join('#' if bit == '1' else ' ' for bit in line))

    return fake_qr

def save_fake_qr(filename, fake_qr):
    """Saves the fake QR code to a file"""
    with open(filename, 'w') as f:
        for line in fake_qr:
            f.write(line + '\n')
    print(f"Fake QR code saved as {filename}")

def main():
    # Check if the correct number of arguments are provided
    if len(sys.argv) != 3:
        print("Usage: python generate_fake_qr.py <data_string> <filename>")
        sys.exit(1)

    # Get the data and filename from the command-line arguments
    data_string = sys.argv[1]
    filename = sys.argv[2]

    # Generate the fake QR code
    fake_qr = generate_fake_qr(data_string)

    # Save the fake QR code to a file
    save_fake_qr(filename, fake_qr)

if __name__ == "__main__":
    main()
