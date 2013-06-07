#ifndef RINGBUFFER_H
#define RINGBUFFER_H

class ringBuffer
{
private:
	unsigned char bytes;
	unsigned char size;
	unsigned char index;
	char *buf;
public:
	ringBuffer(int len);
	~ringBuffer();
	int push(char me);
	int pop();
};

#endif

