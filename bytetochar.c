static void quartet_to_string(const unsigned char val, char* buf)
{
	/* We assume that this value is <= 0xF otherwise it's gonna be bad */
	if (val < 0xA) {
		*buf = (48 + val);
	} else {
		*buf = (55 + val);
	}
}

void byte_to_string(const unsigned char val, char* buf)
{
	unsigned char low_quartet = val & 0x0F;
	unsigned char high_quartet = val >>4;

	quartet_to_string(high_quartet, buf);
	quartet_to_string(low_quartet, buf + 1);
}

