#include<iostream>
#include<string>
#include <vector>

using namespace std;

struct Node {
char** board;
Node* next;
int white_reserve_copy;
int black_reserve_copy;
char active_player_copy;
};
void add(char** board, Node*& head, int size, int white_reserve_copy, int black_reserve_copy, char active_player_copy) {
Node* newNode = new Node;
newNode->board = new char* [2 * size - 1];
for (int i = 0; i < 2 * size - 1; i++) {
	newNode->board[i] = new char[3 * size + 1];
	for (int j = 0; j < 3 * size + 1; j++) {
		newNode->board[i][j] = board[i][j];
	}
}
newNode->white_reserve_copy = white_reserve_copy;
newNode->black_reserve_copy = black_reserve_copy;
newNode->active_player_copy = active_player_copy;
newNode->next = nullptr; Node* curr = head;
if (head == nullptr) {
	head = newNode;
	return;
}
while (curr->next != nullptr) {
	curr = curr->next;
}
curr->next = newNode;
}

int main()
{
int number_array[27] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26 };
char letter_array[26] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','r','s','t','u','w','x','y','z' };
int number_array_index = 1, letter_array_index = 0, board_size = 0, you_can_get_them = 0, num_of_white = 0, num_of_black = 0, num_of_white_reserve = 0, num_of_black_reserve = 0, pomocnicza_numbers = 0, pomocnicza_board_size = 0, pomocnicza_letters = 0,
	pomocnicza_index_numbers = 0, num_of_black_test1 = 0, num_of_white_test1 = 0, board_row_length = 0, expected_row_length_test1 = 0, edging_coordinates_index = 0, to_x_coord = 50, to_y_coord = 0, from_x_coord = 50, from_y_coord = 0, from_array_letter_place,
	to_array_letter_place, row_counter = 0, curret_in_row = 0, num_of_black_abreast = 0, num_of_white_abreast = 0, num_of_wrong_K_rows = 0, putting_x = 0, putting_y, get_from_x = 0, get_from_y = 0, get_to_x = 0, get_to_y = 0, iterator = 0,
	remove_scope_x = 0, remove_scope_y = 0, num_of_uniqe_boards = 0, num_of_visited_boards = 0, nodes = 0, white_reserve_copy = 0, black_reserve_copy = 0;
string command, from_coordinate, to_coordinate, row, enter_coordinates, get_from, get_to;
char active_player, c, tmp1, tmp2, active_white = 'W', active_black = 'B', which_paws, active_player_copy;
bool board_row_length_bool = true, from_to = true, contains_from_coordinate = false, contains_to_coordinate = false, is_next_to_them = true, is_edging_coordinate = false, good_destination = true,
	przesuwanie = true, row_is_full = false, clean_or_not = true, there_is_K_pawn = false, there_is_a_scope = false, color_is_good = true, row_is_good = true, move_made = false, white_in_row = false, black_in_row = false,
	is_board_the_same = true, in_another_way = false, you_can_go_this_row = false;
char** board = nullptr;
char** copy_board = nullptr;
string** board_coordinates = nullptr;
string* edging_coordinates = nullptr;
vector<Node> boards_list;
Node* head = nullptr;

while (cin >> command)
{
	if (command == "LOAD_GAME_BOARD")
	{
		if (clean_or_not == false)
		{
			for (int i = 0; i < 2 * board_size + 1; i++)
			{
				for (int j = 0; j < 4 * board_size + 1; j++)
				{
					board_coordinates[i][j] = "";
				}
			}
			for (int i = 0; i < 6 * board_size; i++)
			{
				edging_coordinates[i] = "";
			}

		}
		num_of_black_test1 = 0;
		num_of_white_test1 = 0;
		board_row_length = 0;
		board_row_length_bool = true;
		edging_coordinates_index = 0;
		num_of_wrong_K_rows = 0;
		there_is_K_pawn = false;
		letter_array_index = 0;
		clean_or_not = false;
		cin >> board_size >> you_can_get_them >> num_of_white >> num_of_black;
		cin >> num_of_white_reserve >> num_of_black_reserve >> active_player;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		pomocnicza_board_size = 3 * board_size - 2;
		board = new char* [2 * board_size - 1];
		copy_board = new char* [2 * board_size - 1];
		expected_row_length_test1 = board_size;
		for (int e = 0; e < 2 * board_size - 1; e++)
		{
			getline(cin, row);
			board[e] = new char[row.length()];
			copy_board[e] = new char[row.length()];
			for (int q = 0; q < row.length(); q++)
			{
				board[e][q] = row[q];
				copy_board[e][q] = row[q];
				if (e < board_size - 1)
				{
					if (board[e][q] == 'W' || board[e][q] == 'B' || board[e][q] == '_')
					{
						if (board[e][q] == 'W')
						{
							num_of_white_test1++;
							if (num_of_white_abreast == 0)
							{
								num_of_white_abreast++;
							}
							else
								if (board[e][q - 2] == 'W')
								{
									num_of_white_abreast++;
								}
						}
						else if (board[e][q] == 'B')
						{
							num_of_black_test1++;
							if (num_of_black_abreast == 0)
							{
								num_of_black_abreast++;
							}
							else
								if (board[e][q - 2] == 'B')
								{
									num_of_black_abreast++;
								}
						}
						else if (board[e][q] == '_')
						{
							if (num_of_white_abreast < you_can_get_them && num_of_black_abreast < you_can_get_them)
							{
								if (q + 2 < row.length())
								{
									if (board[e][q + 2] == 'W' || board[e][q + 2] == 'B')
									{
										num_of_black_abreast = 0;
										num_of_white_abreast = 0;
									}
								}
							}
						}
						board_row_length++;
					}
					if (q == row.length() - 1)
					{
						if (board_row_length != expected_row_length_test1)
						{
							board_row_length_bool = false;
						}
						if (num_of_black_abreast >= you_can_get_them || num_of_white_abreast >= you_can_get_them)
						{
							there_is_K_pawn = true;
							num_of_wrong_K_rows++;
						}
						num_of_black_abreast = 0;
						num_of_white_abreast = 0;
						expected_row_length_test1++;
						board_row_length = 0;
					}
				}
				else if (e >= board_size - 1)
				{
					if (board[e][q] == 'W' || board[e][q] == 'B' || board[e][q] == '_')
					{
						if (board[e][q] == 'W')
						{
							num_of_white_test1++;
							if (num_of_white_abreast == 0)
							{
								num_of_white_abreast++;
							}
							else
								if (board[e][q - 2] == 'W')
								{
									num_of_white_abreast++;
								}
						}
						else if (board[e][q] == 'B')
						{
							num_of_black_test1++;
							if (num_of_black_abreast == 0)
							{
								num_of_black_abreast++;
							}
							else
								if (board[e][q - 2] == 'B')
								{
									num_of_black_abreast++;
								}
						}
						else if (board[e][q] == '_')
						{
							if (num_of_black_abreast < you_can_get_them && num_of_white_abreast < you_can_get_them)
							{
								if (q + 2 < row.length())
								{
									if (board[e][q + 2] == 'W' || board[e][q + 2] == 'B')
									{

										num_of_black_abreast = 0;
										num_of_white_abreast = 0;
									}
								}
							}

						}
						board_row_length++;
					}
					if (q == row.length() - 1)
					{
						if (board_row_length != expected_row_length_test1)
						{
							board_row_length_bool = false;
						}
						if (num_of_black_abreast >= you_can_get_them || num_of_white_abreast >= you_can_get_them)
						{
							there_is_K_pawn = true;
							num_of_wrong_K_rows++;
						}
						num_of_black_abreast = 0;
						num_of_white_abreast = 0;
						expected_row_length_test1--;
						board_row_length = 0;
					}
				}
			}
			row.clear();
		}
		pomocnicza_board_size = board_size - 1;
		pomocnicza_numbers = 0;
		letter_array_index = 0;
		for (int i = 0; i < 2 * board_size - 1; i++)
		{
			putting_x = pomocnicza_board_size;
			putting_y = pomocnicza_numbers;
			while (putting_x >= 0)
			{
				if (board[putting_x][putting_y] == 'W')
				{
					if (num_of_white_abreast == 0)
					{
						num_of_white_abreast++;
					}
					else
						if (board[putting_x + 1][putting_y - 1] == 'W')
						{
							num_of_white_abreast++;
						}
				}
				else if (board[putting_x][putting_y] == 'B')
				{
					if (num_of_black_abreast == 0)
					{
						num_of_black_abreast++;
					}
					else
						if (board[putting_x + 1][putting_y - 1] == 'B')
						{
							num_of_black_abreast++;
						}
				}
				else if (board[putting_x][putting_y] == '_')
				{
					if (num_of_black_abreast < you_can_get_them && num_of_white_abreast < you_can_get_them)
					{
						if (putting_x - 1 >= letter_array_index)
						{
							if (board[putting_x - 1][putting_y + 1] == 'B' || board[putting_x - 1][putting_y + 1] == 'W')
							{
								num_of_black_abreast = 0;
								num_of_white_abreast = 0;
							}
						}
					}
				}
				if (putting_x == letter_array_index)
				{
					if (num_of_black_abreast >= you_can_get_them || num_of_white_abreast >= you_can_get_them)
					{
						there_is_K_pawn = true;
						num_of_wrong_K_rows++;
					}
					num_of_black_abreast = 0;
					num_of_white_abreast = 0;
					break;
				}
				putting_x--;
				putting_y++;
			}
			if (pomocnicza_board_size < 2 * board_size - 2)
			{
				pomocnicza_board_size++;
				pomocnicza_numbers++;
			}
			else
			{
				pomocnicza_numbers = pomocnicza_numbers + 2;
				letter_array_index++;
			}
		}
		letter_array_index = 2 * board_size - 2;
		pomocnicza_board_size = board_size - 1;
		pomocnicza_numbers = 0;
		for (int i = 0; i < 2 * board_size - 1; i++)
		{
			putting_x = pomocnicza_board_size;
			putting_y = pomocnicza_numbers;
			while (putting_x <= 2 * board_size - 2)
			{
				if (board[putting_x][putting_y] == 'W')
				{
					if (num_of_white_abreast == 0)
					{
						num_of_white_abreast++;
					}
					else
						if (board[putting_x - 1][putting_y - 1] == 'W')
						{
							num_of_white_abreast++;
						}
				}
				else if (board[putting_x][putting_y] == 'B')
				{
					if (num_of_black_abreast == 0)
					{
						num_of_black_abreast++;
					}
					else
						if (board[putting_x - 1][putting_y - 1] == 'B')
						{
							num_of_black_abreast++;
						}
				}
				else if (board[putting_x][putting_y] == '_')
				{
					if (num_of_black_abreast < you_can_get_them && num_of_white_abreast < you_can_get_them)
					{
						if (putting_x + 1 <= letter_array_index)
						{
							if (board[putting_x + 1][putting_y + 1] == 'B' || board[putting_x + 1][putting_y + 1] == 'W')
							{
								num_of_black_abreast = 0;
								num_of_white_abreast = 0;
							}
						}
					}
				}
				if (putting_x == letter_array_index)
				{
					if (num_of_black_abreast >= you_can_get_them || num_of_white_abreast >= you_can_get_them)
					{
						there_is_K_pawn = true;
						num_of_wrong_K_rows++;
					}
					num_of_black_abreast = 0;
					num_of_white_abreast = 0;
					break;
				}
				putting_x++;
				putting_y++;
			}
			if (pomocnicza_board_size > 0)
			{
				pomocnicza_board_size--;
				pomocnicza_numbers++;
			}
			else
			{
				pomocnicza_numbers = pomocnicza_numbers + 2;
				letter_array_index--;
			}
		}
		number_array_index = board_size + 1;
		pomocnicza_numbers = board_size + 1;
		pomocnicza_board_size = board_size - 1;
		pomocnicza_letters = 1;
		letter_array_index = 0;
		pomocnicza_index_numbers = 2 * board_size - 1;
		board_coordinates = new string * [2 * board_size + 1];
		edging_coordinates = new string[6 * board_size];

		for (int i = 0; i < 2 * board_size + 1; i++)
		{
			board_coordinates[i] = new string[4 * board_size + 1];
			for (int j = 0; j < 4 * board_size + 1; j++)
			{
				if (i < board_size)
				{
					if (j <= pomocnicza_board_size)
					{
						board_coordinates[i][j] = " ";
					}
					else if (j >= 4 * board_size - pomocnicza_board_size)
					{
						if (j == 4 * board_size)
						{
							board_coordinates[i][j] = " ";
							letter_array_index = 0;
							pomocnicza_numbers--;
							pomocnicza_board_size--;
							number_array_index = pomocnicza_numbers;
						}
						else
							board_coordinates[i][j] = " ";
					}
					else
					{

						if (board_coordinates[i][j - 1] == " ")
						{
							board_coordinates[i][j] = letter_array[letter_array_index] + to_string(number_array[number_array_index]);
							letter_array_index++;
							if (j < pomocnicza_board_size + 2 * board_size + 1)
							{
								number_array_index++;
							}

						}
						else
						{
							board_coordinates[i][j] = " ";
						}
						if (i == 0 && board_coordinates[i][j] != " ")
						{
							edging_coordinates[edging_coordinates_index] = board_coordinates[i][j];
							edging_coordinates_index++;
						}
						else if (i != 0 && board_coordinates[i][j] != " ")
						{
							if (j == pomocnicza_board_size + 1 || j == 4 * board_size - pomocnicza_board_size - 1)
							{
								edging_coordinates[edging_coordinates_index] = board_coordinates[i][j];
								edging_coordinates_index++;
							}
						}

					}
				}
				else if (i == board_size)
				{
					if (j == 4 * board_size)
					{
						board_coordinates[i][j] = letter_array[letter_array_index] + to_string(number_array[number_array_index]);
						pomocnicza_board_size++;
						letter_array_index = pomocnicza_letters;
						number_array_index = 1;
						edging_coordinates[edging_coordinates_index] = board_coordinates[i][j];
						edging_coordinates_index++;

					}
					else if (j - 1 < 0 || board_coordinates[i][j - 1] == " ")
					{
						board_coordinates[i][j] = letter_array[letter_array_index] + to_string(number_array[number_array_index]);
						letter_array_index++;
						if (j < pomocnicza_board_size + 2 * board_size + 1)
						{
							number_array_index++;
						}
					}
					else if (board_coordinates[i][j - 1] != " ")
					{
						board_coordinates[i][j] = " ";

					}
					if (j == 0)
					{
						edging_coordinates[edging_coordinates_index] = board_coordinates[i][j];
						edging_coordinates_index++;
					}
				}
				else
				{
					if (j <= pomocnicza_board_size)
					{
						board_coordinates[i][j] = " ";
					}
					else if (j >= 4 * board_size - pomocnicza_board_size)
					{
						if (j == 4 * board_size)
						{
							board_coordinates[i][j] = " ";
							pomocnicza_letters++;
							letter_array_index = pomocnicza_letters;
							pomocnicza_board_size++;
							pomocnicza_index_numbers--;
							number_array_index = 1;
						}
						else
							board_coordinates[i][j] = " ";
					}
					else
					{
						if (board_coordinates[i][j - 1] == " ")
						{
							board_coordinates[i][j] = letter_array[letter_array_index] + to_string(number_array[number_array_index]);
							letter_array_index++;
							if (j < pomocnicza_index_numbers)
							{
								number_array_index++;
							}

						}
						else
						{
							board_coordinates[i][j] = " ";
						}
					}
					if (i == 2 * board_size && board_coordinates[i][j] != " ")
					{
						edging_coordinates[edging_coordinates_index] = board_coordinates[i][j];
						edging_coordinates_index++;
					}
					else if (i != 2 * board_size && board_coordinates[i][j] != " ")
					{
						if (j == pomocnicza_board_size + 1 || j == 4 * board_size - pomocnicza_board_size - 1)
						{
							edging_coordinates[edging_coordinates_index] = board_coordinates[i][j];
							edging_coordinates_index++;
						}
					}
				}
			}

		}
		if (board_row_length_bool == false)
		{
			cout << "WRONG_BOARD_ROW_LENGTH" << endl;
		}

		else if (num_of_black_test1 > num_of_black - num_of_black_reserve)
		{
			cout << "WRONG_BLACK_PAWNS_NUMBER" << endl;
		}
		else if (num_of_white_test1 > num_of_white - num_of_white_reserve)
		{
			cout << "WRONG_WHITE_PAWNS_NUMBER" << endl;
		}
		else if (there_is_K_pawn == true)
		{
			if (num_of_wrong_K_rows == 1)
			{
				cout << "ERROR_FOUND_" << num_of_wrong_K_rows << "_ROW_OF_LENGTH_K" << endl;
			}
			else
				cout << "ERROR_FOUND_" << num_of_wrong_K_rows << "_ROWS_OF_LENGTH_K" << endl;

		}
		else
		{
			cout << "BOARD_STATE_OK" << endl;
		}
		for (int i = 0; i < 2 * board_size + 1; i++)
		{
			for (int j = 0; j < 4 * board_size + 1; j++)
			{
				cout << board_coordinates[i][j];
			}
			cout << endl;
		}
	}
	else if (command == "PRINT_GAME_BOARD")
	{
		if (board_row_length_bool == true && num_of_black_test1 <= num_of_black - num_of_black_reserve && num_of_white_test1 <= num_of_white - num_of_white_reserve && there_is_K_pawn == false)
		{
			cout << board_size << " " << you_can_get_them << " " << num_of_white << " " << num_of_black << endl;
			cout << num_of_white_reserve << " " << num_of_black_reserve << " " << active_player << endl;
			for (int i = 0; i < 2 * board_size - 1; i++)
			{
				for (int j = 0; j < 3 * board_size + 1; j++)
				{
					if (board[i][j] == ' ' || board[i][j] == '_' || board[i][j] == 'W' || board[i][j] == 'B')
					{
						cout << board[i][j];
					}
					else
						continue;
				}
				cout << endl;
			}
		}
		else
			cout << "EMPTY_BOARD" << endl;
	}
	else if (command == "GEN_ALL_POS_MOV_NUM")
	{
		head = nullptr;
		nodes = 0;
		num_of_uniqe_boards = 0;
		active_player_copy = active_player;
		for (int g = 0; g < 3; g++)
		{
			if (g == 0)
			{
				pomocnicza_board_size = board_size - 1;//poczatek x
				pomocnicza_numbers = 0;//poczatek y
				letter_array_index = 0;//koniec x
				pomocnicza_letters = board_size - 1;//koniec y
			}
			else if (g == 1)
			{
				letter_array_index = 3 * board_size - 3;//koniec y
				pomocnicza_numbers = board_size - 1;//poczatek y
				pomocnicza_board_size = 0;//poczatek x
			}
			else if (g == 2)
			{
				letter_array_index = 2 * board_size - 2;//koniec x
				pomocnicza_board_size = board_size - 1;//poczatek x
				pomocnicza_numbers = 0;//poczatek y
				pomocnicza_letters = board_size - 1;//koniec y
			}
			for (int i = 0; i < 2 * board_size - 1; i++)
			{
				putting_x = pomocnicza_board_size; putting_y = pomocnicza_numbers;
				for (int i = 0; i < 4 * board_size - 2; i++)
				{
					white_reserve_copy = num_of_white_reserve;
					black_reserve_copy = num_of_black_reserve;
					active_player_copy = active_player;
					if (you_can_go_this_row == false)
					{
						while (putting_x >= 0 && putting_y >= 0 && putting_x <= 2 * board_size - 2 && putting_y <= 3 * board_size + 1 && (copy_board[putting_x][putting_y] == 'W' || copy_board[putting_x][putting_y] == 'B' || copy_board[putting_x][putting_y] == '_'))
						{
							if (copy_board[putting_x][putting_y] == '_')
							{
								you_can_go_this_row = true;
								break;
							}
							if (g == 0)
							{
								if (in_another_way == false)
								{
									putting_x--;
									putting_y++;
								}
								else
								{
									putting_x++;
									putting_y--;
								}
							}
							else if (g == 1)
							{
								if (in_another_way == false)
								{
									putting_y += 2;
								}
								else
								{
									putting_y -= 2;
								}
							}
							else if (g == 2)
							{
								if (in_another_way == false)
								{
									putting_x++;
									putting_y++;
								}
								else
								{
									putting_x--;
									putting_y--;
								}
							}
						}
						putting_x = pomocnicza_board_size; putting_y = pomocnicza_numbers;
					}
					if (you_can_go_this_row == true)
					{
						if (copy_board[putting_x][putting_y] == 'W' || copy_board[putting_x][putting_y] == 'B')
						{
							if (iterator == 0)
							{
								tmp1 = copy_board[putting_x][putting_y];
								copy_board[putting_x][putting_y] = active_player_copy;
							}
							else
							{
								if (przesuwanie == true)
								{
									tmp2 = copy_board[putting_x][putting_y];
									copy_board[putting_x][putting_y] = tmp1;
									przesuwanie = false;
								}
								else
								{
									tmp1 = copy_board[putting_x][putting_y];
									copy_board[putting_x][putting_y] = tmp2;
									przesuwanie = true;
								}
							}
						}
						else if (copy_board[putting_x][putting_y] == '_')
						{
							if (iterator == 0)
							{
								copy_board[putting_x][putting_y] = active_player_copy;
								if (active_player_copy == active_white)
								{
									white_reserve_copy--;
									active_player_copy = active_black;
								}
								else if (active_player_copy == active_black)
								{
									black_reserve_copy--;
									active_player_copy = active_white;
								}
							}
							else
							{
								if (przesuwanie == true)
								{
									copy_board[putting_x][putting_y] = tmp1;
									if (active_player_copy == active_white)
									{
										white_reserve_copy--;
										active_player_copy = active_black;
									}
									else if (active_player_copy == active_black)
									{
										black_reserve_copy--;
										active_player_copy = active_white;
									}
								}
								else
								{
									copy_board[putting_x][putting_y] = tmp2;
									if (active_player_copy == active_white)
									{
										white_reserve_copy--;
										active_player_copy = active_black;
									}
									else if (active_player_copy == active_black)
									{
										black_reserve_copy--;
										active_player_copy = active_white;
									}
								}
							}
							if (you_can_go_this_row == true)
							{
								int letter_array_index = 3 * board_size - 2;
								int pomocnicza_board_size = 0;
								for (int i = 0; i < 2 * board_size - 1; i++)
								{
									int putting_x = pomocnicza_board_size;
									int putting_y = 0;
									while (putting_y <= letter_array_index)
									{
										if (copy_board[putting_x][putting_y] == 'W')
										{
											if (num_of_white_abreast == 0)
											{
												num_of_white_abreast++;
											}
											else
												if (copy_board[putting_x][putting_y - 2] == 'W')
												{
													num_of_white_abreast++;
												}
										}
										else if (copy_board[putting_x][putting_y] == 'B')
										{
											if (num_of_black_abreast == 0)
											{
												num_of_black_abreast++;
											}
											else
												if (copy_board[putting_x][putting_y - 2] == 'B')
												{
													num_of_black_abreast++;
												}
										}
										else if (copy_board[putting_x][putting_y] == '_')
										{
											if (num_of_black_abreast < you_can_get_them && num_of_white_abreast < you_can_get_them)
											{
												if (putting_y + 2 < letter_array_index)
												{
													if (copy_board[putting_x][putting_y + 2] == 'W' || copy_board[putting_x][putting_y + 2] == 'B')
													{
														num_of_black_abreast = 0;
														num_of_white_abreast = 0;
													}
												}
											}
											else if (num_of_black_abreast >= you_can_get_them || num_of_white_abreast >= you_can_get_them)
											{
												putting_y = putting_y - 2;;
												while (putting_y >= 0 && copy_board[putting_x][putting_y] != '_')
												{
													if (copy_board[putting_x][putting_y] != '_')
													{
														if (copy_board[putting_x][putting_y] != ' ')
														{
															copy_board[putting_x][putting_y] = '_';
														}
														putting_y = putting_y - 2;
													}
												}
												if (num_of_white_abreast >= you_can_get_them)
												{
													white_reserve_copy += num_of_white_abreast;
												}
												else if (num_of_black_abreast >= you_can_get_them)
												{
													black_reserve_copy += num_of_black_abreast;
												}
												num_of_black_abreast = 0;
												num_of_white_abreast = 0;
											}
										}
										if (putting_y == letter_array_index)
										{
											if (num_of_black_abreast >= you_can_get_them || num_of_white_abreast >= you_can_get_them)
											{
												putting_y = putting_y - 2;
												while (putting_y >= 0)
												{
													if (copy_board[putting_x][putting_y] != '_')
													{
														if (copy_board[putting_x][putting_y] != ' ')
														{
															copy_board[putting_x][putting_y] = '_';
														}
														putting_y = putting_y - 2;
													}
												}
												if (num_of_white_abreast >= you_can_get_them)
												{
													white_reserve_copy += num_of_white_abreast;
												}
												else if (num_of_black_abreast >= you_can_get_them)
												{
													black_reserve_copy += num_of_black_abreast;
												}
											}
											num_of_black_abreast = 0;
											num_of_white_abreast = 0;
											break;
										}
										putting_y++;
									}
									if (pomocnicza_board_size < board_size - 1)
									{
										letter_array_index++;
									}
									else
									{
										letter_array_index--;
									}
									pomocnicza_board_size++;
								}
								pomocnicza_board_size = board_size - 1;
								int pomocnicza_numbers = 0;
								letter_array_index = 0;
								for (int i = 0; i < 2 * board_size - 1; i++)
								{
									putting_x = pomocnicza_board_size;
									putting_y = pomocnicza_numbers;
									while (putting_x >= 0)
									{
										if (copy_board[putting_x][putting_y] == 'W')
										{
											if (num_of_white_abreast == 0)
											{
												num_of_white_abreast++;
											}
											else
												if (copy_board[putting_x + 1][putting_y - 1] == 'W')
												{
													num_of_white_abreast++;
												}
										}
										else if (copy_board[putting_x][putting_y] == 'B')
										{
											if (num_of_black_abreast == 0)
											{
												num_of_black_abreast++;
											}
											else
												if (copy_board[putting_x + 1][putting_y - 1] == 'B')
												{
													num_of_black_abreast++;
												}
										}
										else if (copy_board[putting_x][putting_y] == '_')
										{
											if (num_of_black_abreast < you_can_get_them && num_of_white_abreast < you_can_get_them)
											{
												if (putting_x - 1 >= letter_array_index)
												{
													if (copy_board[putting_x - 1][putting_y + 1] == 'B' || copy_board[putting_x - 1][putting_y + 1] == 'W')
													{
														num_of_black_abreast = 0;
														num_of_white_abreast = 0;
													}
												}
											}
											else if (num_of_black_abreast >= you_can_get_them || num_of_white_abreast >= you_can_get_them)
											{
												putting_x++;
												putting_y--;
												while (putting_x <= pomocnicza_board_size && copy_board[putting_x][putting_y] != '_')
												{
													copy_board[putting_x][putting_y] = '_';
													putting_x++;
													putting_y--;
												}
												if (num_of_white_abreast >= you_can_get_them)
												{
													white_reserve_copy += num_of_white_abreast;
												}
												else if (num_of_black_abreast >= you_can_get_them)
												{
													black_reserve_copy += num_of_black_abreast;
												}
												num_of_black_abreast = 0;
												num_of_white_abreast = 0;
												break;
											}
										}
										if (putting_x == letter_array_index)
										{
											if (num_of_black_abreast >= you_can_get_them || num_of_white_abreast >= you_can_get_them)
											{
												while (putting_x <= pomocnicza_board_size && copy_board[putting_x][putting_y] != '_')
												{
													copy_board[putting_x][putting_y] = '_';
													putting_x++;
													putting_y--;
												}
												if (num_of_white_abreast >= you_can_get_them)
												{
													white_reserve_copy += num_of_white_abreast;
												}
												else if (num_of_black_abreast >= you_can_get_them)
												{
													black_reserve_copy += num_of_black_abreast;
												}
											}
											num_of_black_abreast = 0;
											num_of_white_abreast = 0;
											break;
										}
										putting_x--;
										putting_y++;
									}
									if (pomocnicza_board_size < 2 * board_size - 2)
									{
										pomocnicza_board_size++;
										pomocnicza_numbers++;
									}
									else
									{
										pomocnicza_numbers = pomocnicza_numbers + 2;
										letter_array_index++;
									}
								}
								letter_array_index = 2 * board_size - 2;
								pomocnicza_board_size = board_size - 1;
								pomocnicza_numbers = 0;
								for (int i = 0; i < 2 * board_size - 1; i++)
								{
									putting_x = pomocnicza_board_size;
									putting_y = pomocnicza_numbers;
									while (putting_x <= 2 * board_size - 2)
									{
										if (copy_board[putting_x][putting_y] == 'W')
										{
											if (num_of_white_abreast == 0)
											{
												num_of_white_abreast++;
											}
											else
												if (copy_board[putting_x - 1][putting_y - 1] == 'W')
												{
													num_of_white_abreast++;
												}
										}
										else if (copy_board[putting_x][putting_y] == 'B')
										{
											if (num_of_black_abreast == 0)
											{
												num_of_black_abreast++;
											}
											else
												if (copy_board[putting_x - 1][putting_y - 1] == 'B')
												{
													num_of_black_abreast++;
												}
										}
										else if (copy_board[putting_x][putting_y] == '_')
										{
											if (num_of_black_abreast < you_can_get_them && num_of_white_abreast < you_can_get_them)
											{
												if (putting_x + 1 <= letter_array_index)
												{
													if (copy_board[putting_x + 1][putting_y + 1] == 'B' || copy_board[putting_x + 1][putting_y + 1] == 'W')
													{
														num_of_black_abreast = 0;
														num_of_white_abreast = 0;
													}
												}
											}
											else if (num_of_black_abreast >= you_can_get_them || num_of_white_abreast >= you_can_get_them)
											{
												putting_x--;
												putting_y--;
												while (putting_x >= pomocnicza_board_size && copy_board[putting_x][putting_y] != '_')
												{
													copy_board[putting_x][putting_y] = '_';
													putting_x--;
													putting_y--;
												}
												if (num_of_white_abreast >= you_can_get_them)
												{
													white_reserve_copy += num_of_white_abreast;
												}
												else if (num_of_black_abreast >= you_can_get_them)
												{
													black_reserve_copy += num_of_black_abreast;
												}
												num_of_black_abreast = 0;
												num_of_white_abreast = 0;
												break;
											}
										}
										if (putting_x == letter_array_index)
										{
											if (num_of_black_abreast >= you_can_get_them || num_of_white_abreast >= you_can_get_them)
											{
												while (putting_x >= pomocnicza_board_size && copy_board[putting_x][putting_y] != '_')
												{
													copy_board[putting_x][putting_y] = '_';
													putting_x--;
													putting_y--;
												}

												if (num_of_white_abreast >= you_can_get_them)
												{
													white_reserve_copy += num_of_white_abreast;
												}
												else if (num_of_black_abreast >= you_can_get_them)
												{
													black_reserve_copy += num_of_black_abreast;
												}
											}
											num_of_black_abreast = 0;
											num_of_white_abreast = 0;
											break;
										}
										putting_x++;
										putting_y++;
									}
									if (pomocnicza_board_size > 0)
									{
										pomocnicza_board_size--;
										pomocnicza_numbers++;
									}
									else
									{
										pomocnicza_numbers = pomocnicza_numbers + 2;
										letter_array_index--;
									}
								}
							}
							if (head == nullptr)
							{
								add(copy_board, head, board_size, white_reserve_copy, black_reserve_copy, active_player_copy);
								nodes++;
								for (int i = 0; i < 2 * board_size - 1; i++)
								{
									for (int j = 0; j < 3 * board_size + 1; j++)
									{
										if (board[i][j] == ' ' || board[i][j] == '_' || board[i][j] == 'W' || board[i][j] == 'B')
										{
											copy_board[i][j] = board[i][j];
										}
										else
											continue;
									}
								}
								num_of_uniqe_boards++;
							}
							else
							{
								Node* traverse = head;
								do
								{
									for (int i = 0; i < 2 * board_size - 1; i++)
									{
										for (int j = 0; j < 3 * board_size + 1; j++)
										{
											if (board[i][j] == ' ' || board[i][j] == '_' || board[i][j] == 'W' || board[i][j] == 'B')
											{
												if (traverse->board[i][j] != copy_board[i][j])
												{
													is_board_the_same = false;
													break;
												}
											}
											else
												continue; }
										if (is_board_the_same == false)
										{
											num_of_visited_boards++;
											is_board_the_same = true; break;
										}
									}
									traverse = traverse->next;
								} while (traverse != nullptr);
								if (num_of_visited_boards == nodes)
								{
									num_of_uniqe_boards++; num_of_visited_boards = 0; is_board_the_same = true; add(copy_board, head, board_size, white_reserve_copy, black_reserve_copy, active_player_copy); nodes++;

								}
								for (int i = 0; i < 2 * board_size - 1; i++)
								{
									for (int j = 0; j < 3 * board_size + 1; j++)
									{
										if (board[i][j] == ' ' || board[i][j] == '_' || board[i][j] == 'W' || board[i][j] == 'B')
										{
											copy_board[i][j] = board[i][j];
										}
										else
											continue;
									}
								}
							}
							if (g == 0)
							{
								if (in_another_way == false)
								{
									num_of_visited_boards = 0; is_board_the_same = true; in_another_way = true; iterator = -1; putting_x = letter_array_index - 1; putting_y = pomocnicza_letters + 1, przesuwanie = true;
								}
								else
								{
									num_of_visited_boards = 0; is_board_the_same = true; in_another_way = true; break;
								}
							}
							else if (g == 1)
							{
								if (in_another_way == false)
								{
									num_of_visited_boards = 0; is_board_the_same = true; in_another_way = true; iterator = -1; putting_x = pomocnicza_board_size; putting_y = letter_array_index + 2, przesuwanie = true;
								}
								else
								{
									num_of_visited_boards = 0; is_board_the_same = true; in_another_way = true; break;
								}
							}
							else if (g == 2)
							{
								if (in_another_way == false)
								{
									num_of_visited_boards = 0; is_board_the_same = true; in_another_way = true; iterator = -1; putting_x = letter_array_index + 1; putting_y = pomocnicza_letters + 1, przesuwanie = true;
								}
								else
								{
									num_of_visited_boards = 0;	is_board_the_same = true;	in_another_way = true;	break;
								}
							}
						}
						if (g == 0)
						{
							if (in_another_way == false)
							{
								putting_x--; putting_y++;
							}
							else
							{
								putting_x++; putting_y--;
							}
						}
						else if (g == 1)
						{
							if (in_another_way == false)
							{
								putting_y += 2;
							}
							else
							{
								putting_y -= 2;
							}
						}
						else if (g == 2)
						{
							if (in_another_way == false)
							{
								putting_x++; putting_y++;
							}
							else
							{
								putting_x--; putting_y--;
							}
						}
					}
					if (you_can_go_this_row == false)
						break;
					iterator++;
				}
				if (g == 0)
				{
					if (pomocnicza_board_size < 2 * board_size - 2)
					{
						pomocnicza_board_size++; pomocnicza_numbers++;
						pomocnicza_letters += 2;
					}
					else
					{
						pomocnicza_numbers = pomocnicza_numbers + 2; letter_array_index++;
						pomocnicza_letters++;
					}
					in_another_way = false;
					you_can_go_this_row = false;
					iterator = 0;
					przesuwanie = true;
					active_player_copy = active_player;
				}
				else if (g == 1)
				{
					if (pomocnicza_board_size < board_size - 1)
					{
						letter_array_index++;
						pomocnicza_numbers--;
					}
					else
					{
						letter_array_index--;
						pomocnicza_numbers++;
					}
					pomocnicza_board_size++;
					you_can_go_this_row = false;
					in_another_way = false;
					iterator = 0;
					przesuwanie = true;
					active_player_copy = active_player;
				}
				else if (g == 2)
				{
					if (pomocnicza_board_size > 0)
					{
						pomocnicza_board_size--; pomocnicza_numbers++;	pomocnicza_letters += 2;
					}
					else
					{
						pomocnicza_numbers = pomocnicza_numbers + 2; letter_array_index--;	pomocnicza_letters++;
					}
					you_can_go_this_row = false;
					in_another_way = false;
					iterator = 0;
					przesuwanie = true;
					active_player_copy = active_player;
				}
			}
		}
		cout << num_of_uniqe_boards << "_UNIQUE_MOVES" << endl;
	}
	else if (command == "GEN_ALL_POS_MOV" && head != nullptr)
	{
		Node* traverse = head;
		do
		{
			cout << board_size << " " << you_can_get_them << " " << num_of_white << " " << num_of_white << endl;
			cout << traverse->white_reserve_copy << " " << traverse->black_reserve_copy << " " << traverse->active_player_copy << endl;
			for (int i = 0; i < 2 * board_size - 1; i++)
			{
				for (int j = 0; j < 3 * board_size + 1; j++)
				{
					if (traverse->board[i][j] == ' ' || traverse->board[i][j] == '_' || traverse->board[i][j] == 'W' || traverse->board[i][j] == 'B')
					{
						cout << traverse->board[i][j];
					}
					else
						continue;
				}
				cout << endl;
			}
			cout << endl;
			traverse = traverse->next;
		} while (traverse != nullptr);
	}
	else if (command == "DO_MOVE")
	{
		cin.ignore(numeric_limits<streamsize>::max(), ' ');
		getline(cin, enter_coordinates);
		if (enter_coordinates.length() > 5)
		{
			from_coordinate = enter_coordinates[0]; from_coordinate += enter_coordinates[1];
			to_coordinate = enter_coordinates[3]; to_coordinate += enter_coordinates[4];
			which_paws = enter_coordinates[6];
			get_from = enter_coordinates[9]; get_from += enter_coordinates[10];
			get_to = enter_coordinates[12]; get_to += enter_coordinates[13];
			there_is_a_scope = true;
		}
		else
		{
			from_coordinate = enter_coordinates[0]; from_coordinate += enter_coordinates[1];
			to_coordinate = enter_coordinates[3]; to_coordinate += enter_coordinates[4];
		}
		if (there_is_a_scope == true)
		{
			for (int i = 0; i < 2 * board_size + 1; i++)
			{
				for (int j = 0; j < 4 * board_size + 1; j++)
				{
					if (board_coordinates[i][j] == get_from)
					{
						get_from_x = i - 1; get_from_y = j - 2;
					}
					else if (board_coordinates[i][j] == get_to)
					{
						get_to_x = i - 1; get_to_y = j - 2;
					}
				}
			}
		}
		for (int i = 0; i < 26; i++)
		{
			if (letter_array[i] == from_coordinate[0])
			{
				from_array_letter_place = i;
				break;
			}
		}
		for (int j = 0; j < 26; j++)
		{
			if (letter_array[j] == to_coordinate[0])
			{
				to_array_letter_place = j;
				break;
			}
		}
		for (int l = 0; l < 2 * board_size + 1; l++)
		{
			for (int v = 0; v < 4 * board_size + 1; v++)
			{
				if (board_coordinates[l][v] == from_coordinate)
				{
					contains_from_coordinate = true;
					break;
				}
			}
			if (contains_from_coordinate == true)
			{
				break;
			}
		}
		for (int l = 0; l < 2 * board_size + 1; l++)
		{
			for (int v = 0; v < 4 * board_size + 1; v++)
			{
				if (board_coordinates[l][v] == to_coordinate)
				{
					contains_to_coordinate = true;
					break;
				}
			}
			if (contains_to_coordinate == true)
			{
				break;
			}
		}
		if (contains_from_coordinate == false || contains_to_coordinate == false)
		{
			if (contains_from_coordinate == false && contains_to_coordinate == false)
			{
				cout << "BAD_MOVE_" << from_coordinate << "_IS_WRONG_INDEX" << endl;
			}
			else if (contains_from_coordinate == false)
			{
				cout << "BAD_MOVE_" << from_coordinate << "_IS_WRONG_INDEX" << endl;
			}
			else if (contains_to_coordinate == false)
			{
				cout << "BAD_MOVE_" << to_coordinate << "_IS_WRONG_INDEX" << endl;
			}
		}
		if (contains_from_coordinate == true && contains_to_coordinate == true)
		{
			if ((to_array_letter_place != from_array_letter_place && to_array_letter_place != from_array_letter_place + 1 && to_array_letter_place != from_array_letter_place - 1) || (from_coordinate[1] != to_coordinate[1] && from_coordinate[1] != to_coordinate[1] - 1 && from_coordinate[1] != to_coordinate[1] + 1))
			{
				is_next_to_them = false;
				cout << "UNKNOWN_MOVE_DIRECTION" << endl;
			}

		}
		if (is_next_to_them == true && contains_from_coordinate == true && contains_to_coordinate == true)
		{
			for (int i = 0; i < 6 * board_size; i++)
			{
				if (edging_coordinates[i] == from_coordinate)
				{
					is_edging_coordinate = true;
					break;
				}
			}
			if (is_edging_coordinate == false && contains_from_coordinate == true && contains_to_coordinate == true)
			{
				cout << "BAD_MOVE_" << from_coordinate << "_IS_WRONG_STARTING_FIELD" << endl;
			}
			if (is_edging_coordinate == true && contains_from_coordinate == true && contains_to_coordinate == true)
			{
				for (int i = 0; i < 6 * board_size; i++)
				{
					if (edging_coordinates[i] == to_coordinate)
					{
						good_destination = false;
						cout << "BAD_MOVE_" << to_coordinate << "_IS_WRONG_DESTINATION_FIELD" << endl;
						break;
					}
				}
			}
		}
		if (good_destination == true && contains_from_coordinate == true && contains_to_coordinate == true && is_next_to_them == true && is_edging_coordinate == true)
		{
			for (int i = 0; i < 2 * board_size + 1; i++)
			{
				for (int j = 0; j < 4 * board_size + 1; j++)
				{
					if (board_coordinates[i][j] == to_coordinate)
					{
						to_x_coord = i;
						to_y_coord = j;
						break;
					}
				}
				if (to_x_coord == i)
				{
					break;
				}
			}
			for (int i = 0; i < 2 * board_size + 1; i++)
			{
				for (int j = 0; j < 4 * board_size + 1; j++)
				{
					if (board_coordinates[i][j] == from_coordinate)
					{
						from_x_coord = i;
						from_y_coord = j;
						break;
					}
				}
				if (from_x_coord == i)
				{
					break;
				}
			}
			putting_x = to_x_coord - 1;
			putting_y = to_y_coord - 2;
			do
			{
				if (board[putting_x][putting_y] == 'W' || board[putting_x][putting_y] == 'B' || board[putting_x][putting_y] == '_')
				{
					if (board[putting_x][putting_y] == 'W' || board[putting_x][putting_y] == 'B')
					{
						curret_in_row++;
						row_counter++;
					}
					else
						row_counter++;
				}
				if (from_x_coord < to_x_coord && from_y_coord < to_y_coord)//zwiekaszmy wiersz i kolumne
				{
					putting_x++;
					putting_y++;
				}
				else if (from_x_coord > to_x_coord && from_y_coord > to_y_coord)//zmniejszamy wiersz i kolumne
				{
					putting_x--;
					putting_y--;
				}
				else if (from_x_coord < to_x_coord && from_y_coord > to_y_coord)//zwiekszamy wiersz zmniejszmy kolumne
				{
					putting_x++;
					putting_y--;
				}
				else if (from_x_coord > to_x_coord && from_y_coord < to_y_coord)//zmniejszmy wiersz zwiekszamy kolumne
				{
					putting_x--;
					putting_y++;
				}
				else if (from_x_coord == to_x_coord && from_y_coord < to_y_coord)//wiersz zostaje zwiekszamy kolumne
				{
					putting_y = putting_y + 2;
				}
				else if (from_x_coord == to_x_coord && from_y_coord > to_y_coord)//wiersz zostaje zmniejszamy kolumne
				{
					putting_y = putting_y - 2;
				}
				if (putting_x < 0 || putting_y < 0 || putting_x > 2 * board_size - 2 || putting_y>3 * board_size || board[putting_x][putting_y] == ' ')
				{
					if (curret_in_row == row_counter)
					{
						row_is_full = true;
						cout << "BAD_MOVE_ROW_IS_FULL" << endl;
					}
					break;
				}
			} while (board[putting_x][putting_y] != ' ' && putting_x >= 0 && putting_x <= 2 * board_size - 2 && putting_y >= 0 && putting_y <= 3 * board_size);
			if (row_is_full == false)
			{
				putting_x = to_x_coord - 1;
				putting_y = to_y_coord - 2;
				for (int i = 0; i < 2 * board_size - 1; i++)
				{
					if (board[putting_x][putting_y] == 'W' || board[putting_x][putting_y] == 'B')
					{
						if (i == 0)
						{
							tmp1 = board[putting_x][putting_y];
							board[putting_x][putting_y] = active_player;
						}
						else
						{
							if (przesuwanie == true)
							{
								tmp2 = board[putting_x][putting_y];
								board[putting_x][putting_y] = tmp1;
								przesuwanie = false;
							}
							else
							{
								tmp1 = board[putting_x][putting_y];
								board[putting_x][putting_y] = tmp2;
								przesuwanie = true;
							}
						}
						if (from_x_coord < to_x_coord && from_y_coord < to_y_coord)//zwiekaszmy wiersz i kolumne
						{
							putting_x++;
							putting_y++;
						}
						else if (from_x_coord > to_x_coord && from_y_coord > to_y_coord)//zmniejszamy wiersz i kolumne
						{
							putting_x--;
							putting_y--;
						}
						else if (from_x_coord < to_x_coord && from_y_coord > to_y_coord)//zwiekszamy wiersz zmniejszmy kolumne
						{
							putting_x++;
							putting_y--;
						}
						else if (from_x_coord > to_x_coord && from_y_coord < to_y_coord)//zmniejszmy wiersz zwiekszamy kolumne
						{
							putting_x--;
							putting_y++;
						}
						else if (from_x_coord == to_x_coord && from_y_coord < to_y_coord)//wiersz zostaje zwiekszamy kolumne
						{
							putting_y = putting_y + 2;
						}
						else if (from_x_coord == to_x_coord && from_y_coord > to_y_coord)//wiersz zostaje zmniejszamy kolumne
						{
							putting_y = putting_y - 2;
						}

					}
					else
					{
						if (i == 0)
						{
							board[putting_x][putting_y] = active_player;
							if (active_player == active_white)
							{
								num_of_white_reserve--;
								num_of_white_test1++;
								active_player = active_black;
							}
							else
							{
								num_of_black_reserve--;
								num_of_black_test1++;
								active_player = active_white;
							}
						}
						else
						{
							if (przesuwanie == true)
							{
								board[putting_x][putting_y] = tmp1;
								if (active_player == active_white)
								{
									num_of_white_reserve--;
									num_of_white_test1++;
									active_player = active_black;
								}
								else
								{
									num_of_black_reserve--;
									num_of_black_test1++;
									active_player = active_white;
								}
							}
							else
							{
								board[putting_x][putting_y] = tmp2;
								if (active_player == active_white)
								{
									num_of_white_reserve--;
									num_of_white_test1++;
									active_player = active_black;
								}
								else
								{
									num_of_black_reserve--;
									num_of_black_test1++;
									active_player = active_white;
								}

							}
						}
						if (there_is_a_scope == true)
						{
							remove_scope_x = get_from_x;
							remove_scope_y = get_from_y;
							while (board[remove_scope_x][remove_scope_y] != '_')
							{
								if (board[remove_scope_x][remove_scope_y] == 'W')
									num_of_white_abreast++;
								else if (board[remove_scope_x][remove_scope_y] == 'B')
									num_of_black_abreast++;
								if (remove_scope_x == get_to_x && remove_scope_y == get_to_y)
								{
									if (num_of_white_abreast < you_can_get_them && num_of_black_abreast < you_can_get_them)
									{
										cout << "WRONG_INDEX_OF_CHOSEN_ROW" << endl;
										row_is_good = false;
										num_of_black_abreast = 0; num_of_white_abreast = 0;
									}
									else if (num_of_black_abreast >= you_can_get_them)
									{
										black_in_row = true;
										num_of_black_abreast = 0; num_of_white_abreast = 0;
									}
									else if (num_of_white_abreast >= you_can_get_them)
									{
										white_in_row = true;
										num_of_black_abreast = 0; num_of_white_abreast = 0;
									}
									break;
								}

								if (get_from_x < get_to_x && get_from_y < get_to_y)//zwiekaszmy wiersz i kolumne
								{
									remove_scope_x++;
									remove_scope_y++;
								}
								else if (get_from_x > get_to_x && get_from_y > get_to_y)//zmniejszamy wiersz i kolumne
								{
									remove_scope_x--;
									remove_scope_y--;
								}
								else if (get_from_x < get_to_x && get_from_y > get_to_y)//zwiekszamy wiersz zmniejszmy kolumne
								{
									remove_scope_x++;
									remove_scope_y--;
								}
								else if (get_from_x > get_to_x && get_from_y < get_to_y)//zmniejszmy wiersz zwiekszamy kolumne
								{
									remove_scope_x--;
									remove_scope_y++;
								}
								else if (get_from_x == get_to_x && get_from_y < get_to_y)//wiersz zostaje zwiekszamy kolumne
								{
									remove_scope_y = remove_scope_y + 2;
								}
								else if (get_from_x == get_to_x && get_from_y > get_to_y)//wiersz zostaje zmniejszamy kolumne
								{
									remove_scope_y = remove_scope_y - 2;
								}
							}
							if (row_is_good == true)
							{
								if (which_paws == 'b')
								{
									if (black_in_row == false)
									{
										cout << "WRONG_COLOR_OF_CHOSEN_ROW" << endl;
										color_is_good = false;
									}
								}
								else if (which_paws == 'w')
								{
									if (white_in_row == false)
									{
										cout << "WRONG_COLOR_OF_CHOSEN_ROW" << endl;
										color_is_good = false;
									}
								}
							}
						}
						if (color_is_good == true && row_is_good == true)
						{
							cout << "MOVE_COMMITTED" << endl;
							move_made = true;
						}
						if (move_made == true || color_is_good == false || row_is_good == false)
							break;
					}
				}
			}
		}
		if (there_is_a_scope == true && row_is_good == true && color_is_good == true)
		{
			remove_scope_x = get_from_x;
			remove_scope_y = get_from_y;
			while (remove_scope_x >= 0 && remove_scope_x <= 2 * board_size - 2 && remove_scope_y >= 0 && remove_scope_y <= 3 * board_size + 1 && (board[remove_scope_x][remove_scope_y] == 'W' || board[remove_scope_x][remove_scope_y] == 'B'))
			{
				if (board[remove_scope_x][remove_scope_y] == 'W')
					num_of_white_abreast++;
				else if (board[remove_scope_x][remove_scope_y] == 'B')
					num_of_black_abreast++;
				board[remove_scope_x][remove_scope_y] = '_';
				if (get_from_x < get_to_x && get_from_y < get_to_y)//zwiekaszmy wiersz i kolumne
				{
					remove_scope_x++;
					remove_scope_y++;
					if (remove_scope_x < 0 || remove_scope_x > 2 * board_size - 2 || remove_scope_y < 0 || remove_scope_y > 3 * board_size + 1 ||
						board[remove_scope_x][remove_scope_y] != 'W' && board[remove_scope_x][remove_scope_y] != 'B')
					{
						remove_scope_x = get_from_x - 1;
						remove_scope_y = get_from_y - 1;
						while (remove_scope_x >= 0 && remove_scope_x <= 2 * board_size - 2 && remove_scope_y >= 0 && remove_scope_y <= 3 * board_size + 1 && (board[remove_scope_x][remove_scope_y] == 'W' || board[remove_scope_x][remove_scope_y] == 'B'))
						{
							if (board[remove_scope_x][remove_scope_y] == 'W')
								num_of_white_abreast++;
							else if (board[remove_scope_x][remove_scope_y] == 'B')
								num_of_black_abreast++;
							board[remove_scope_x][remove_scope_y] = '_';
							remove_scope_x--;
							remove_scope_y--;
						}
						if (num_of_white_abreast >= you_can_get_them)
						{
							num_of_white_reserve += num_of_white_abreast;
							num_of_white_test1 -= num_of_white_abreast;
						}
						else if (num_of_black_abreast >= you_can_get_them)
						{
							num_of_black_reserve += num_of_black_abreast;
							num_of_black_test1 -= num_of_black_abreast;
						}
						num_of_black_abreast = 0; num_of_white_abreast = 0;
						break;
					}
				}
				else if (get_from_x > get_to_x && get_from_y > get_to_y)//zmniejszamy wiersz i kolumne
				{
					remove_scope_x--;
					remove_scope_y--;
					if (remove_scope_x < 0 || remove_scope_x > 2 * board_size - 2 || remove_scope_y < 0 || remove_scope_y > 3 * board_size + 1 ||
						board[remove_scope_x][remove_scope_y] != 'W' && board[remove_scope_x][remove_scope_y] != 'B')
					{
						remove_scope_x = get_from_x + 1;
						remove_scope_y = get_from_y + 1;
						while (remove_scope_x >= 0 && remove_scope_x <= 2 * board_size - 2 && remove_scope_y >= 0 && remove_scope_y <= 3 * board_size + 1 && (board[remove_scope_x][remove_scope_y] == 'W' || board[remove_scope_x][remove_scope_y] == 'B'))
						{
							if (board[remove_scope_x][remove_scope_y] == 'W')
								num_of_white_abreast++;
							else if (board[remove_scope_x][remove_scope_y] == 'B')
								num_of_black_abreast++;
							board[remove_scope_x][remove_scope_y] = '_';
							remove_scope_x++;
							remove_scope_y++;
						}
						if (num_of_white_abreast >= you_can_get_them)
						{
							num_of_white_reserve += num_of_white_abreast;
							num_of_white_test1 -= num_of_white_abreast;
						}
						else if (num_of_black_abreast >= you_can_get_them)
						{
							num_of_black_reserve += num_of_black_abreast;
							num_of_black_test1 -= num_of_black_abreast;
						}
						num_of_black_abreast = 0; num_of_white_abreast = 0;
						break;
					}
				}
				else if (get_from_x < get_to_x && get_from_y > get_to_y)//zwiekszamy wiersz zmniejszmy kolumne
				{
					remove_scope_x++;
					remove_scope_y--;
					if (remove_scope_x < 0 || remove_scope_x > 2 * board_size - 2 || remove_scope_y < 0 || remove_scope_y > 3 * board_size + 1 ||
						board[remove_scope_x][remove_scope_y] != 'W' && board[remove_scope_x][remove_scope_y] != 'B')
					{
						remove_scope_x = get_from_x - 1;
						remove_scope_y = get_from_y + 1;
						while (remove_scope_x >= 0 && remove_scope_x <= 2 * board_size - 2 && remove_scope_y >= 0 && remove_scope_y <= 3 * board_size + 1 && (board[remove_scope_x][remove_scope_y] == 'W' || board[remove_scope_x][remove_scope_y] == 'B'))
						{
							if (board[remove_scope_x][remove_scope_y] == 'W')
								num_of_white_abreast++;
							else if (board[remove_scope_x][remove_scope_y] == 'B')
								num_of_black_abreast++;
							board[remove_scope_x][remove_scope_y] = '_';
							remove_scope_x--;
							remove_scope_y++;
						}
						if (num_of_white_abreast >= you_can_get_them)
						{
							num_of_white_reserve += num_of_white_abreast;
							num_of_white_test1 -= num_of_white_abreast;
						}
						else if (num_of_black_abreast >= you_can_get_them)
						{
							num_of_black_reserve += num_of_black_abreast;
							num_of_black_test1 -= num_of_black_abreast;
						}
						num_of_black_abreast = 0; num_of_white_abreast = 0;
						break;
					}
				}
				else if (get_from_x > get_to_x && get_from_y < get_to_y)//zmniejszmy wiersz zwiekszamy kolumne
				{
					remove_scope_x--;
					remove_scope_y++;
					if (remove_scope_x < 0 || remove_scope_x > 2 * board_size - 2 || remove_scope_y < 0 || remove_scope_y > 3 * board_size + 1 ||
						board[remove_scope_x][remove_scope_y] != 'W' && board[remove_scope_x][remove_scope_y] != 'B')
					{
						remove_scope_x = get_from_x + 1;
						remove_scope_y = get_from_y - 1;
						while (remove_scope_x >= 0 && remove_scope_x <= 2 * board_size - 2 && remove_scope_y >= 0 && remove_scope_y <= 3 * board_size + 1 && (board[remove_scope_x][remove_scope_y] == 'W' || board[remove_scope_x][remove_scope_y] == 'B'))
						{
							if (board[remove_scope_x][remove_scope_y] == 'W')
								num_of_white_abreast++;
							else if (board[remove_scope_x][remove_scope_y] == 'B')
								num_of_black_abreast++;
							board[remove_scope_x][remove_scope_y] = '_';
							remove_scope_x++;
							remove_scope_y--;
						}
						if (num_of_white_abreast >= you_can_get_them)
						{
							num_of_white_reserve += num_of_white_abreast;
							num_of_white_test1 -= num_of_white_abreast;
						}
						else if (num_of_black_abreast >= you_can_get_them)
						{
							num_of_black_reserve += num_of_black_abreast;
							num_of_black_test1 -= num_of_black_abreast;
						}
						num_of_black_abreast = 0; num_of_white_abreast = 0;
						break;
					}
				}
				else if (get_from_x == get_to_x && get_from_y < get_to_y)//wiersz zostaje zwiekszamy kolumne
				{
					remove_scope_y = remove_scope_y + 2;
					if (remove_scope_x < 0 || remove_scope_x > 2 * board_size - 2 || remove_scope_y < 0 || remove_scope_y > 3 * board_size + 1 ||
						board[remove_scope_x][remove_scope_y] != 'W' && board[remove_scope_x][remove_scope_y] != 'B')
					{
						remove_scope_x = get_from_x;
						remove_scope_y = get_from_y - 2;
						while (remove_scope_x >= 0 && remove_scope_x <= 2 * board_size - 2 && remove_scope_y >= 0 && remove_scope_y <= 3 * board_size + 1 && (board[remove_scope_x][remove_scope_y] == 'W' || board[remove_scope_x][remove_scope_y] == 'B'))
						{
							if (board[remove_scope_x][remove_scope_y] == 'W')
								num_of_white_abreast++;
							else if (board[remove_scope_x][remove_scope_y] == 'B')
								num_of_black_abreast++;
							board[remove_scope_x][remove_scope_y] = '_';
							remove_scope_y = remove_scope_y - 2;
						}
						if (num_of_white_abreast >= you_can_get_them)
						{
							num_of_white_reserve += num_of_white_abreast;
							num_of_white_test1 -= num_of_white_abreast;
						}
						else if (num_of_black_abreast >= you_can_get_them)
						{
							num_of_black_reserve += num_of_black_abreast;
							num_of_black_test1 -= num_of_black_abreast;
						}
						num_of_black_abreast = 0; num_of_white_abreast = 0;
						break;
					}
				}
				else if (get_from_x == get_to_x && get_from_y > get_to_y)//wiersz zostaje zmniejszamy kolumne
				{
					remove_scope_y = remove_scope_y - 2;
					if (remove_scope_x < 0 || remove_scope_x > 2 * board_size - 2 || remove_scope_y < 0 || remove_scope_y > 3 * board_size + 1 ||
						board[remove_scope_x][remove_scope_y] != 'W' && board[remove_scope_x][remove_scope_y] != 'B')
					{
						remove_scope_x = get_from_x;
						remove_scope_y = get_from_y + 2;
						while (remove_scope_x >= 0 && remove_scope_x <= 2 * board_size - 2 && remove_scope_y >= 0 && remove_scope_y <= 3 * board_size + 1 && (board[remove_scope_x][remove_scope_y] == 'W' || board[remove_scope_x][remove_scope_y] == 'B'))
						{
							if (board[remove_scope_x][remove_scope_y] == 'W')
								num_of_white_abreast++;
							else if (board[remove_scope_x][remove_scope_y] == 'B')
								num_of_black_abreast++;
							board[remove_scope_x][remove_scope_y] = '_';
							remove_scope_y = remove_scope_y + 2;
						}
						if (num_of_white_abreast >= you_can_get_them)
						{
							num_of_white_reserve += num_of_white_abreast;
							num_of_white_test1 -= num_of_white_abreast;
						}
						else if (num_of_black_abreast >= you_can_get_them)
						{
							num_of_black_reserve += num_of_black_abreast;
							num_of_black_test1 -= num_of_black_abreast;
						}
						num_of_black_abreast = 0; num_of_white_abreast = 0;
						break;
					}
				}
			}

		}
		letter_array_index = 3 * board_size - 2;
		pomocnicza_board_size = 0;
		for(int i=0;i<2*board_size-1;i++)
		{
			putting_x = pomocnicza_board_size;
			putting_y = 0;
			while (putting_y <= letter_array_index)
			{
				if (board[putting_x][putting_y] == 'W')
				{
					if (num_of_white_abreast == 0)
					{
						num_of_white_abreast++;
					}
					else
						if (board[putting_x][putting_y - 2] == 'W')
						{
							num_of_white_abreast++;
						}
				}
				else if (board[putting_x][putting_y] == 'B')
				{
					if (num_of_black_abreast == 0)
					{
						num_of_black_abreast++;
					}
					else
						if (board[putting_x][putting_y - 2] == 'B')
						{
							num_of_black_abreast++;
						}
				}
				else if (board[putting_x][putting_y] == '_')
				{
					if (num_of_black_abreast < you_can_get_them && num_of_white_abreast < you_can_get_them)
					{
						if (putting_y + 2 < letter_array_index)
						{
							if (board[putting_x][putting_y + 2] == 'W' || board[putting_x][putting_y + 2] == 'B')
							{
								num_of_black_abreast = 0;
								num_of_white_abreast = 0;
							}
						}
					}
					else if (num_of_black_abreast >= you_can_get_them || num_of_white_abreast >= you_can_get_them)
					{
						putting_y = putting_y - 2;;
						while (putting_y >= 0 && board[putting_x][putting_y] != '_')
						{
							if (board[putting_x][putting_y] != '_')
							{
								if (board[putting_x][putting_y] != ' ')
								{
									board[putting_x][putting_y] = '_';
								}
								putting_y = putting_y - 2;
							}
						}
						if (num_of_white_abreast >= you_can_get_them)
						{
							num_of_white_reserve += num_of_white_abreast;
							num_of_white_test1 -= num_of_white_abreast;
						}
						else if (num_of_black_abreast >= you_can_get_them)
						{
							num_of_black_reserve += num_of_black_abreast;
							num_of_black_test1 -= num_of_black_abreast;
						}
						num_of_black_abreast = 0;
						num_of_white_abreast = 0;
					}

				}
				if (putting_y == letter_array_index)
				{
					if (num_of_black_abreast >= you_can_get_them || num_of_white_abreast >= you_can_get_them)
					{
						putting_y = putting_y - 2;
						while (putting_y >= 0)
						{
							if (board[putting_x][putting_y] != '_')
							{
								if (board[putting_x][putting_y] != ' ')
								{
									board[putting_x][putting_y] = '_';
								}
								putting_y = putting_y - 2;
							}
						}
						if (num_of_white_abreast >= you_can_get_them)
						{
							num_of_white_reserve += num_of_white_abreast;
							num_of_white_test1 -= num_of_white_abreast;
						}
						else if (num_of_black_abreast >= you_can_get_them)
						{
							num_of_black_reserve += num_of_black_abreast;
							num_of_black_test1 -= num_of_black_abreast;
						}
						num_of_black_abreast = 0;
						num_of_white_abreast = 0;
					}
					num_of_black_abreast = 0;
					num_of_white_abreast = 0;
					break;
				}
				putting_y++;
			}
			if (pomocnicza_board_size < board_size - 1)
			{
				letter_array_index++;
			}
			else
			{
				letter_array_index--;
			}
			pomocnicza_board_size++;
		}
		pomocnicza_board_size = board_size - 1;
		pomocnicza_numbers = 0;
		letter_array_index = 0;
		for (int i = 0; i < 2 * board_size - 1; i++)
		{
			putting_x = pomocnicza_board_size;
			putting_y = pomocnicza_numbers;
			while (putting_x >= 0)
			{
				if (board[putting_x][putting_y] == 'W')
				{
					if (num_of_white_abreast == 0)
					{
						num_of_white_abreast++;
					}
					else
						if (board[putting_x + 1][putting_y - 1] == 'W')
						{
							num_of_white_abreast++;
						}
				}
				else if (board[putting_x][putting_y] == 'B')
				{
					if (num_of_black_abreast == 0)
					{
						num_of_black_abreast++;
					}
					else
						if (board[putting_x + 1][putting_y - 1] == 'B')
						{
							num_of_black_abreast++;
						}
				}
				else if (board[putting_x][putting_y] == '_')
				{
					if (num_of_black_abreast < you_can_get_them && num_of_white_abreast < you_can_get_them)
					{
						if (putting_x - 1 >= letter_array_index)
						{
							if (board[putting_x - 1][putting_y + 1] == 'B' || board[putting_x - 1][putting_y + 1] == 'W')
							{
								num_of_black_abreast = 0;
								num_of_white_abreast = 0;
							}
						}
					}
					else if (num_of_black_abreast >= you_can_get_them || num_of_white_abreast >= you_can_get_them)
					{
						putting_x++;
						putting_y--;
						while (putting_x <= pomocnicza_board_size && board[putting_x][putting_y] != '_')
						{
							board[putting_x][putting_y] = '_';
							putting_x++;
							putting_y--;
						}
						if (num_of_white_abreast >= you_can_get_them)
						{
							num_of_white_reserve += num_of_white_abreast;
							num_of_white_test1 -= num_of_white_abreast;
						}
						else if (num_of_black_abreast >= you_can_get_them)
						{
							num_of_black_reserve += num_of_black_abreast;
							num_of_black_test1 -= num_of_black_abreast;
						}
						num_of_black_abreast = 0;
						num_of_white_abreast = 0;
						break;
					}
				}
				if (putting_x == letter_array_index)
				{
					if (num_of_black_abreast >= you_can_get_them || num_of_white_abreast >= you_can_get_them)
					{
						while (putting_x <= pomocnicza_board_size && board[putting_x][putting_y] != '_')
						{
							board[putting_x][putting_y] = '_';
							putting_x++;
							putting_y--;
						}
						if (num_of_white_abreast >= you_can_get_them)
						{
							num_of_white_reserve += num_of_white_abreast;
							num_of_white_test1 -= num_of_white_abreast;
						}
						else if (num_of_black_abreast >= you_can_get_them)
						{
							num_of_black_reserve += num_of_black_abreast;
							num_of_black_test1 -= num_of_black_abreast;
						}
					}
					num_of_black_abreast = 0;
					num_of_white_abreast = 0;
					break;
				}
				putting_x--;
				putting_y++;
			}
			if (pomocnicza_board_size < 2 * board_size - 2)
			{
				pomocnicza_board_size++;
				pomocnicza_numbers++;
			}
			else
			{
				pomocnicza_numbers = pomocnicza_numbers + 2;
				letter_array_index++;
			}
		}
		letter_array_index = 2 * board_size - 2;
		pomocnicza_board_size = board_size - 1;
		pomocnicza_numbers = 0;
		for (int i = 0; i < 2 * board_size - 1; i++)
		{
			putting_x = pomocnicza_board_size;
			putting_y = pomocnicza_numbers;
			while (putting_x <= 2 * board_size - 2)
			{
				if (board[putting_x][putting_y] == 'W')
				{
					if (num_of_white_abreast == 0)
					{
						num_of_white_abreast++;
					}
					else
						if (board[putting_x - 1][putting_y - 1] == 'W')
						{
							num_of_white_abreast++;
						}
				}
				else if (board[putting_x][putting_y] == 'B')
				{
					if (num_of_black_abreast == 0)
					{
						num_of_black_abreast++;
					}
					else
						if (board[putting_x - 1][putting_y - 1] == 'B')
						{
							num_of_black_abreast++;
						}
				}
				else if (board[putting_x][putting_y] == '_')
				{
					if (num_of_black_abreast < you_can_get_them && num_of_white_abreast < you_can_get_them)
					{
						if (putting_x + 1 <= letter_array_index)
						{
							if (board[putting_x + 1][putting_y + 1] == 'B' || board[putting_x + 1][putting_y + 1] == 'W')
							{
								num_of_black_abreast = 0;
								num_of_white_abreast = 0;
							}
						}
					}
					else if (num_of_black_abreast >= you_can_get_them || num_of_white_abreast >= you_can_get_them)
					{
						putting_x--;
						putting_y--;
						while (putting_x >= pomocnicza_board_size && board[putting_x][putting_y] != '_')
						{
							board[putting_x][putting_y] = '_';
							putting_x--;
							putting_y--;
						}
						if (num_of_white_abreast >= you_can_get_them)
						{
							num_of_white_reserve += num_of_white_abreast;
							num_of_white_test1 -= num_of_white_abreast;
						}
						else if (num_of_black_abreast >= you_can_get_them)
						{
							num_of_black_reserve += num_of_black_abreast;
							num_of_black_test1 -= num_of_black_abreast;
						}
						num_of_black_abreast = 0;
						num_of_white_abreast = 0;
						break;
					}
				}
				if (putting_x == letter_array_index)
				{
					if (num_of_black_abreast >= you_can_get_them || num_of_white_abreast >= you_can_get_them)
					{
						while (putting_x >= pomocnicza_board_size && board[putting_x][putting_y] != '_')
						{
							board[putting_x][putting_y] = '_';
							putting_x--;
							putting_y--;
						}

						if (num_of_white_abreast >= you_can_get_them)
						{
							num_of_white_reserve += num_of_white_abreast;
							num_of_white_test1 -= num_of_white_abreast;
						}
						else if (num_of_black_abreast >= you_can_get_them)
						{
							num_of_black_reserve += num_of_black_abreast;
							num_of_black_test1 -= num_of_black_abreast;
						}
					}
				num_of_black_abreast = 0;
					num_of_white_abreast = 0;
					break;
				}
				putting_x++;
				putting_y++;
			}
			if (pomocnicza_board_size > 0)
			{
				pomocnicza_board_size--;
				pomocnicza_numbers++;
			}
			else
			{
				pomocnicza_numbers = pomocnicza_numbers + 2;
				letter_array_index--;
			}
		}
		from_to = true; contains_to_coordinate = false; contains_from_coordinate = false; is_next_to_them = true; is_edging_coordinate = false; good_destination = true; przesuwanie = true; row_is_full = false;
		from_coordinate.clear(); to_coordinate.clear(); get_from.clear(); get_to.clear(); from_x_coord = 50; enter_coordinates.clear(); to_x_coord = 50; curret_in_row = 0; row_counter = 0; letter_array_index = 0;
		there_is_a_scope = false; color_is_good = true; row_is_good = true; move_made = false; white_in_row = false; black_in_row = false;
	}
}
return 0;

}