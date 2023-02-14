# TODO

def main():
    # Check if user inputted the correct values
    height = input("Height: ")
    height = height_check(height)
    while (height == 0):
        height = input("Height: ")
        height = height_check(height)

    n_row = 1
    while (n_row <= height):
        print_spaces(height, n_row)  #
        print_hashtag(n_row)  # Draw the left side
        print("  ", end="")  # Space in between to separate
        print_hashtag(n_row)  # Draw the right side
        print()  # Then moves on to next line
        n_row += 1


def print_spaces(height, n_row):
    column = n_row
    while (column < height):
        print(" ", end="")  # Print spaces
        column += 1


def print_hashtag(n_row):
    column = 1
    while (column <= n_row):
        print("#", end="")
        column += 1


def height_check(user_input):
    # Only accept 1 - 8 numbers and numbers only
    try:
        user_input = int(user_input)
        if (user_input >= 1) and (user_input <= 8):
            return user_input
        pass
    except ValueError:
        pass
    return 0  # The input didn't violated any rules


if __name__ == "__main__":
    main()