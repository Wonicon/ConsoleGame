#include "console.h"
#include <Windows.h>
#include <assert.h>


SMALL_RECT windowSize = { 0, 0, WIDTH - 1, HEIGHT - 1 };
COORD bufferSize = { WIDTH, HEIGHT };
COORD charBufferSize = { WIDTH, HEIGHT };
COORD InitPos = { 0, 0 };

static HANDLE     hStdin;                  // 控制台输入句柄
static HANDLE     hStdout;                 // 控制台输出句柄
static HWND       hWin;                    // 窗口句柄
static CHAR_INFO  buffer[HEIGHT * WIDTH];  // 字符缓冲区

void InitConsole(void)
{
	// 获得句柄
	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	hWin = GetForegroundWindow();
	// 控制台光标设置为不可见
	CONSOLE_CURSOR_INFO info = { 1, 0 };
	SetConsoleCursorInfo(hStdout, &info);

	SetConsoleScreenBufferSize(hStdout, bufferSize);
	SetConsoleTitleA(TITLE);
	if (SetConsoleWindowInfo(hStdout, TRUE, &windowSize)) {
		//assert(0);
	}
}
// 检测当前窗口是否激活
bool IsWindowActive(void)
{
	return hWin == GetForegroundWindow();
}
// 重绘缓冲区
void RedrawConsole(void)
{
	WriteConsoleOutputA(hStdout, buffer, bufferSize, InitPos, &windowSize);
}
// 写入缓冲区
void WriteChar(int x, int y, CHAR_INFO ch)
{
	assert(BOUNDARY_CHECK(x, y));
	buffer[x + y * WIDTH] = ch;
}
// 绘制字符串
void WriteString(int x, int y, const char *str, int len, int attr)
{
	CHAR_INFO ch;
	ch.Attributes = attr;
	int index = x + y * WIDTH;
	assert(0 <= index && index + len <= WIDTH * HEIGHT);
	for (int i = 0; i < len; i++) {
		ch.Char.INPUT_CHAR = *str++;
		buffer[index++] = ch;
	}
}
// 绘制竖线
void WriteColumn(int x, int y, const char *str, int len, int attr)
{
	CHAR_INFO ch;
	ch.Attributes = attr;
	int index = x + y * WIDTH;
	assert(0 <= index && index + len <= WIDTH * HEIGHT);
	for (int i = 0; i < len; i++) {
		ch.Char.AsciiChar = *str++;
		buffer[index] = ch;
		index += WIDTH;
	}
}
// 绘制矩形
void WriteBlock(COORD pos, COORD size, CHAR_INFO str[])
{
	int index = pos.X + pos.Y * WIDTH;
	int i = 0;
	for (int y = 0; y < size.Y; y++) {
		for (int x = 0; x < size.X; x++) {
			if (str[i].Char.AsciiChar != JMP_CHAR) {
				buffer[index + x] = str[i];
			}
			i++;
		}
		index += WIDTH;
	}
}
// 修改属性
void ModifyAttribute(int x, int y, int attr)
{
	assert(BOUNDARY_CHECK(x, y));
	buffer[x + y * WIDTH].Attributes = attr;
}
// 清空缓冲区
void ClearConsoleBuffer(void)
{
	memset(buffer, 0, WIDTH * HEIGHT * sizeof(CHAR_INFO));
}