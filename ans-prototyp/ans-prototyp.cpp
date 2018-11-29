// ans-prototyp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <algorithm>
#include <cassert>
#include <tuple>
#include <array>
#include <iostream>


unsigned char reverse_byte(unsigned char x)
{
	static const unsigned char table[] = {
		0x00, 0x80, 0x40, 0xc0, 0x20, 0xa0, 0x60, 0xe0,
		0x10, 0x90, 0x50, 0xd0, 0x30, 0xb0, 0x70, 0xf0,
		0x08, 0x88, 0x48, 0xc8, 0x28, 0xa8, 0x68, 0xe8,
		0x18, 0x98, 0x58, 0xd8, 0x38, 0xb8, 0x78, 0xf8,
		0x04, 0x84, 0x44, 0xc4, 0x24, 0xa4, 0x64, 0xe4,
		0x14, 0x94, 0x54, 0xd4, 0x34, 0xb4, 0x74, 0xf4,
		0x0c, 0x8c, 0x4c, 0xcc, 0x2c, 0xac, 0x6c, 0xec,
		0x1c, 0x9c, 0x5c, 0xdc, 0x3c, 0xbc, 0x7c, 0xfc,
		0x02, 0x82, 0x42, 0xc2, 0x22, 0xa2, 0x62, 0xe2,
		0x12, 0x92, 0x52, 0xd2, 0x32, 0xb2, 0x72, 0xf2,
		0x0a, 0x8a, 0x4a, 0xca, 0x2a, 0xaa, 0x6a, 0xea,
		0x1a, 0x9a, 0x5a, 0xda, 0x3a, 0xba, 0x7a, 0xfa,
		0x06, 0x86, 0x46, 0xc6, 0x26, 0xa6, 0x66, 0xe6,
		0x16, 0x96, 0x56, 0xd6, 0x36, 0xb6, 0x76, 0xf6,
		0x0e, 0x8e, 0x4e, 0xce, 0x2e, 0xae, 0x6e, 0xee,
		0x1e, 0x9e, 0x5e, 0xde, 0x3e, 0xbe, 0x7e, 0xfe,
		0x01, 0x81, 0x41, 0xc1, 0x21, 0xa1, 0x61, 0xe1,
		0x11, 0x91, 0x51, 0xd1, 0x31, 0xb1, 0x71, 0xf1,
		0x09, 0x89, 0x49, 0xc9, 0x29, 0xa9, 0x69, 0xe9,
		0x19, 0x99, 0x59, 0xd9, 0x39, 0xb9, 0x79, 0xf9,
		0x05, 0x85, 0x45, 0xc5, 0x25, 0xa5, 0x65, 0xe5,
		0x15, 0x95, 0x55, 0xd5, 0x35, 0xb5, 0x75, 0xf5,
		0x0d, 0x8d, 0x4d, 0xcd, 0x2d, 0xad, 0x6d, 0xed,
		0x1d, 0x9d, 0x5d, 0xdd, 0x3d, 0xbd, 0x7d, 0xfd,
		0x03, 0x83, 0x43, 0xc3, 0x23, 0xa3, 0x63, 0xe3,
		0x13, 0x93, 0x53, 0xd3, 0x33, 0xb3, 0x73, 0xf3,
		0x0b, 0x8b, 0x4b, 0xcb, 0x2b, 0xab, 0x6b, 0xeb,
		0x1b, 0x9b, 0x5b, 0xdb, 0x3b, 0xbb, 0x7b, 0xfb,
		0x07, 0x87, 0x47, 0xc7, 0x27, 0xa7, 0x67, 0xe7,
		0x17, 0x97, 0x57, 0xd7, 0x37, 0xb7, 0x77, 0xf7,
		0x0f, 0x8f, 0x4f, 0xcf, 0x2f, 0xaf, 0x6f, 0xef,
		0x1f, 0x9f, 0x5f, 0xdf, 0x3f, 0xbf, 0x7f, 0xff,
	};
	return table[x];
}



std::pair<int, int> get_number_of_bit_shifts_needed_to_get_back_to_octave(const int octave_length, int starting_number)
{
	auto iterations = 0;
	while(starting_number < octave_length)
	{
		starting_number <<= 1;
		++iterations;
	}
	return { iterations, starting_number };
}

//uint8_t reverse_byte(const char byte)
//{
//	return ((byte * 0x0802LU & 0x22110LU) | (byte * 0x8020LU & 0x88440LU)) * 0x10101LU >> 16;
//}

int reverse_int(const int source)
{
	int reversed;  // this is reverse of getal

	char *n1, *n2;
	n1 = (char *)&source;
	n2 = (char *)&reversed;

	*(n2 + 0) = reverse_byte(*(n1 + 3));  // or n2[0] = n1[3];
	*(n2 + 1) = reverse_byte(*(n1 + 2));  // or n2[1] = n1[2];
	*(n2 + 2) = reverse_byte(*(n1 + 1));  // or n2[2] = n1[1]; 
	*(n2 + 3) = reverse_byte(*(n1 + 0));  // or n2[3] = n1[0];
	return reversed;
}

void calculate_less_probable_symbol_states(int less_probable_symbol_index) {}

int main()
{

	const auto octave_length = 512;

	const auto probability_of_zero = 0.7;

	const auto probability_of_one = 1 - probability_of_zero;

	std::array<std::vector<int>, 4> decoder_look_up_table;

	for(auto& vec : decoder_look_up_table)
	{
		vec.resize(octave_length, -1);
	}

	int ranges[2] = { static_cast<int>(round(probability_of_zero * octave_length)) , static_cast<int>(round(probability_of_one * octave_length)) };

	int max_value_value[2] = { ranges[0] * 2 - 1, ranges[1] * 2 - 1 };

	const auto max_range = std::max(ranges[0], ranges[1]);

	std::array<std::vector<int>, 2> encoder_look_up_table;

	for (auto& vec : encoder_look_up_table)
	{
		vec.resize(max_range * 2);
	}

	const auto more_probable_symbol_index = probability_of_zero > 0.5 ? 0 : 1; 

	const auto less_probable_symbol_index = (more_probable_symbol_index + 1) % 2;

	//more probable symbol encode LUT initialization ***********************************************

	for(auto symbol_index = 0; symbol_index < ranges[more_probable_symbol_index]; ++symbol_index)
	{
		encoder_look_up_table[more_probable_symbol_index][symbol_index] = -1;
	}

	for (auto symbol_index = ranges[more_probable_symbol_index]; symbol_index < ranges[more_probable_symbol_index] * 2; ++symbol_index)
	{
		auto next_state_temp = (symbol_index + 1) / probability_of_zero;
		auto next_state = static_cast<int>(std::round(std::ceil((symbol_index + 1) / probability_of_zero))) - 1;
		if (next_state_temp - std::floor(next_state_temp) < 0.000000001)
		{
			next_state = static_cast<int>((symbol_index + 1) / probability_of_zero) - 1;
		}

		const auto renormalization_parameters = get_number_of_bit_shifts_needed_to_get_back_to_octave(octave_length, symbol_index);
		assert(encoder_look_up_table[more_probable_symbol_index][symbol_index] != -1);
		assert(encoder_look_up_table[more_probable_symbol_index][symbol_index] == 0);

		encoder_look_up_table[more_probable_symbol_index][symbol_index] = next_state;
		next_state -= octave_length;
		assert(decoder_look_up_table[1][next_state] == -1);

		decoder_look_up_table[0][next_state] = more_probable_symbol_index;
		decoder_look_up_table[1][next_state] = symbol_index;
		decoder_look_up_table[2][next_state] = renormalization_parameters.first;
		decoder_look_up_table[3][next_state] = renormalization_parameters.second;
	}

	for(auto symbol_index = ranges[0] * 2; symbol_index < max_range * 2; ++symbol_index)
	{
		encoder_look_up_table[more_probable_symbol_index][symbol_index] = -1;
	}
	//**********************************************************************************



	//less probable symbol encode LUT initialization ***********************************************
	for (auto symbol_index = 0; symbol_index < ranges[less_probable_symbol_index]; ++symbol_index)
	{
		encoder_look_up_table[less_probable_symbol_index][symbol_index] = -1;
	}

	for (auto symbol_index = ranges[less_probable_symbol_index]; symbol_index < ranges[less_probable_symbol_index] * 2; ++symbol_index)
	{
		const auto next_state_temp = symbol_index / probability_of_one;
		auto next_state = static_cast<int>(std::floor(symbol_index / probability_of_one));
//		std::cout << " KEK " << next_state_temp - std::ceil(next_state_temp) << std::endl;
		if(std::ceil(next_state_temp) - next_state_temp < 0.00000000001)
		{
//			std::cout<< "omegalul " << std::endl;
			next_state++;
		}
//		std::cout << symbol_index << std::endl;
//		std::cout << (symbol_index / probability_of_one) << std::endl;
		const auto renormalization_parameters = get_number_of_bit_shifts_needed_to_get_back_to_octave(octave_length, symbol_index);
//		std::cout << next_state << std::endl << std::endl;

		assert(encoder_look_up_table[less_probable_symbol_index][symbol_index] != -1);
		assert(encoder_look_up_table[less_probable_symbol_index][symbol_index] == 0);

		encoder_look_up_table[less_probable_symbol_index][symbol_index] = next_state;
		next_state -= octave_length;
		assert(decoder_look_up_table[1][next_state] == -1);


		decoder_look_up_table[0][next_state] = less_probable_symbol_index;
		decoder_look_up_table[1][next_state] = symbol_index;
		decoder_look_up_table[2][next_state] = renormalization_parameters.first;
		decoder_look_up_table[3][next_state] = renormalization_parameters.second;

	}

	for (auto symbol_index = ranges[less_probable_symbol_index] * 2; symbol_index < max_range * 2; ++symbol_index)
	{
		encoder_look_up_table[less_probable_symbol_index][symbol_index] = -1;
	}
	//**********************************************************************************

	std::cout << "octave_state: index, symbol" << std::endl;
	for(auto i = 0; i < octave_length; ++i)
	{
		std::cout << i + octave_length << ": " << decoder_look_up_table[1][i] << ", " << decoder_look_up_table[0][i] << ", " << decoder_look_up_table[2][i] << ", " << decoder_look_up_table[3][i] << std::endl;
	}


	std::vector<int> sequence_to_be_coded = { 111111, 1231231, 2929389, 33333 };

	std::cout << "Encoded sequence: ";
	for (auto i = 0; i < sequence_to_be_coded.size(); ++i)
	{
		std::cout << sequence_to_be_coded[i];
	}
	std::cout << std::endl;

	std::reverse(sequence_to_be_coded.begin(), sequence_to_be_coded.end());

	for(auto& integer : sequence_to_be_coded)
	{
		integer = reverse_int(integer);
	}

	std::vector<int> encoded_sequence;

	std::vector<int> decoded_sequence;

	auto state = octave_length;
//	std::cout << state << std::endl;
	for(auto i = 0; i < sequence_to_be_coded.size() * 8; ++i)
	{
		const auto value_to_be_encoded = sequence_to_be_coded[i];
		while(state > max_value_value[value_to_be_encoded])
		{
			encoded_sequence.push_back(state & 0x1);
			state >>= 1;
		}
		state = encoder_look_up_table[value_to_be_encoded][state];
//		std::cout << state << std::endl;
	}

	while(state > 0)
	{
		encoded_sequence.push_back(state & 0x1);
		state >>= 1;
	}

//	std::cout << "Already encoded sequence: ";
//	for (auto i = 0; i < encoded_sequence.size(); ++i)
//	{
//		std::cout << encoded_sequence[i];
//	}
//	std::cout << std::endl;
	int encoded_length = encoded_sequence.size();


	while (!encoded_sequence.empty() && state < octave_length)
	{
		state = (state << 1) + encoded_sequence.back();
		encoded_sequence.pop_back();
	}
//	std::cout << state << ": ";
//	for(int i = encoded_sequence.size() -1; i >= 0 ; --i)
//	{
//		std::cout << encoded_sequence[i];
//	}
//	std::cout << std::endl;

	while(!encoded_sequence.empty())
	{

		const auto index = state - octave_length;
		decoded_sequence.push_back(decoder_look_up_table[0][index]);

		state = decoder_look_up_table[3][index];

		auto bits = 0;
		for(auto i = 0; i < decoder_look_up_table[2][index]; ++i)
		{
			bits = (bits << 1) + encoded_sequence.back();
			encoded_sequence.pop_back();
		}

		state += bits;

//		std::cout << state << ": ";
//		for (int i = encoded_sequence.size() - 1; i >= 0; --i)
//		{
//			std::cout << encoded_sequence[i];
//		}
//		std::cout << std::endl;
//		

	}

	std::reverse(decoded_sequence.begin(), decoded_sequence.end());

	std::cout << "Decoded sequence: ";
	for(auto i = 0; i < decoded_sequence.size(); ++i)
	{
		std::cout << decoded_sequence[i] << (i == decoded_sequence.size() - 1 ? ", " : "");
	}

	std::cout << "Length: " << decoded_sequence.size();
	std::cout << "Encoded length: " << encoded_length << std::endl;


	return 0;

}

