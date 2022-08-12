#include<math.h>
#include "dft.h"
#include "coefficients1024.h"


void dft(DTYPE real_sample[1024], DTYPE imag_sample[1024],DTYPE real_op[1024],DTYPE imag_op[1024])
{
#pragma HLS INTERFACE s_axilite port=return
#pragma HLS INTERFACE m_axi depth=100 port=real_sample offset=slave
#pragma HLS INTERFACE m_axi depth=100 port=imag_sample offset=slave
#pragma HLS INTERFACE m_axi depth=100 port=real_op offset=slave
#pragma HLS INTERFACE m_axi depth=100 port=imag_op offset=slave

	//Write your code here
	for(int i=0; i<1024; i++){

		DTYPE tmp_real_op = 0, tmp_imag_op = 0;
		DTYPE w_cos = 1;
		DTYPE w_sin = 0;
		DTYPE interval_cos = cos_coefficients_table[i];
		DTYPE interval_sin = sin_coefficients_table[i];


		for(int j=0; j<1024; j++){
#pragma HLS PIPELINE II=1

			DTYPE tmp_real = real_sample[j];
			DTYPE tmp_imag = imag_sample[j];

			tmp_real_op += tmp_real*w_cos - tmp_imag*w_sin;
			tmp_imag_op += tmp_imag*w_cos + tmp_real*w_sin;

			DTYPE tmp_cos = w_cos;
			DTYPE tmp_sin = w_sin;
			w_sin = tmp_cos*interval_sin + tmp_sin*interval_cos;
			w_cos = tmp_cos*interval_cos - tmp_sin*interval_sin;

		}
		real_op[i] = tmp_real_op;
		imag_op[i] = tmp_imag_op;
	}
}
