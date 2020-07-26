__kernel void MyCLAdd(__global unsigned char *frame_u, __global unsigned char *frame_d, __global unsigned char *m_foregroundMatchCount, __global unsigned char *m_mask, __global unsigned char *m_samples, __global unsigned char *_image, __global int *random_s, __global int *random_n, __global int *random_9, const int ran, __global int *c_xoff, __global int *c_yoff, __global int *flag, const int N, const int rows, const int cols, const int NUM_SAMPLES, const int RADIUS, const int MIN_MATCHES, const int SUBSAMPLE_FACTOR)
{
	int i = get_global_id(0);
	int matches = 0, count = 0;
	int dist;
	int r = i + ran;
	int image = _image[i];
	int temp;
	m_mask[i] = 0;
	while (matches != MIN_MATCHES && count != NUM_SAMPLES)
	{
		temp = count * N + i;
		dist = (m_samples[temp] - image);
		if (-RADIUS < dist && dist < RADIUS)
			++matches;
		++count;
	}
	if (matches == MIN_MATCHES)
	{
		m_foregroundMatchCount[i] = 0;
		if (random_s[r] == 0)
		{
			m_samples[random_n[r] * N + i] = image;
		}
		if (random_s[r] == 0)
		{
			if (!flag[i])
			{
				int row;
				row = i + c_yoff[random_9[r]] * cols + c_xoff[random_9[r + 1]];
				if (row<N)
					m_samples[random_n[r] * N + row] = image;
			}
		}
	}
	else
	{
		++m_foregroundMatchCount[i];
		m_mask[i] = 255;
		if (m_foregroundMatchCount[i] > 10)
		{
			if (random_s[r] == 0)
			{
				m_samples[random_n[r] * N + i] = image;
			}
		}
	}
}