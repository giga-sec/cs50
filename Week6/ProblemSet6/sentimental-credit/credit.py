from sys import exit


def main():
    cc_num = int(input("Number:"))
    cc_len = digit_length(cc_num)
    if cc_len in [15, 16, 13]:
        legit_card = luhn_algor(cc_num)
        if (legit_card == True):
            print_cc_type(cc_num, cc_len)
            return 0
    print("INVALID")
    return 1


def print_cc_type(cc_num, cc_len):
    if (cc_len == 15):
        cc_num = cc_num // (10**13)  # 13 because 15 - 2
        if (cc_num == 37) or (cc_num == 34):
            print("AMEX")
    elif (cc_len == 16):
        cc_num = cc_num // (10**14)  # 14 because 16 - 2, and 2 because we want to left 2 numbers
        if cc_num in [51, 52, 53, 54, 55]:
            print("MASTERCARD")

        cc_num = cc_num // 10
        if (cc_num == 4):
            print("VISA")
    elif (cc_len == 13):
        cc_num = cc_num // (10**12)
        if (temp2 == 4):
            print("VISA")


def luhn_algor(cc_num):
    sum = 0
    first_last_digit = 0
    while (cc_num > 0):
        sec_last_digit = ((cc_num // 10) % 10)  # Get the second to the last digit
        first_last_digit = first_last_digit + (cc_num % 10)

        # Skip if 0
        if (sec_last_digit == 0):
            cc_num = cc_num // 100
            continue

        sec_last_digit = sec_last_digit * 2
        # Multiplied number must not exceed with 2 digits
        if (sec_last_digit >= 10):
            first_digit = sec_last_digit % 10
            sec_digit = sec_last_digit // 10
            sec_last_digit = first_digit + sec_digit
        sum = sum + sec_last_digit
        cc_num = cc_num // 100  # Remove last two digits
    sum = (first_last_digit + sum) % 10
    if (sum == 0):
        return True  # Legit
    return False  # Not legit


def digit_length(num):
    count = 0
    while (num > 0):
        num = num // 10
        count += 1
    return count


if __name__ == "__main__":
    main()
