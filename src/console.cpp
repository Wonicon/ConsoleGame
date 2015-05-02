#include "console.h"
#include <Windows.h>
#include <assert.h>

const SMALL_RECT windowSize = { 0, 0, WIDTH - 1, HEIGHT - 1 };
const COORD bufferSize = { WIDTH, HEIGHT };
const COORD charBufferSize = { WIDTH, HEIGHT };
const COORD initPos = { 0, 0 };

static HANDLE hStdin;                  // 控制台输入句柄
static HANDLE hStdout;                 // 控制台输出句柄
static HWND   hWin;                    // 窗口句柄
#ifndef COLOR
static CHAR   screen[HEIGHT * WIDTH];  // 屏幕字符缓冲区
#else
static CHAR_INFO screen[HEIGHT * WIDTH];
#define DEFAULT_STR_ATTR (FOREGROUND_GREEN)
static int string_attr = DEFAULT_STR_ATTR;
#endif

inline int BufIndex(int x, int y)
{
	return x + y * WIDTH;
}
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
	SetConsoleWindowInfo(hStdout, TRUE, &windowSize);
	//SetConsoleOutputCP(437);
}
// 检测当前窗口是否激活
bool IsWindowActive(void)
{
	return hWin == GetForegroundWindow();
}
// 重绘缓冲区
void RedrawConsole(void)
{
#ifndef COLOR
	SetConsoleCursorPosition(hStdout, initPos);
	DWORD rst;
	WriteConsoleA(hStdout, screen, HEIGHT * WIDTH - 1, &rst, NULL);
#else
	static SMALL_RECT win = windowSize;
	WriteConsoleOutputA(hStdout, screen, bufferSize, initPos, &win);
#endif
}

// 绘制字符串
void WriteString(int x, int y, CHAR str[])
{
#ifndef COLOR
	int index = x + y * WIDTH;
	memcpy(screen + index, str, strlen(str));
#else
	int i = BufIndex(x, y);
	int j = 0;
	while (str[j] != '\0') {
		screen[i].Attributes = string_attr;
		screen[i].Char.AsciiChar = str[j];
		i++;
		j++;
	}
#endif
}
// 绘制竖线
void WriteColumn(int x, int y, CHAR str[])
{
	int index = x + y * WIDTH;
	int len = strlen(str);
	for (int i = 0; i < len; i++) {
#ifndef COLOR
		screen[index] = *str++;
#else
		screen[index].Attributes = string_attr;
		screen[index].Char.AsciiChar = str[i];
#endif
		index += WIDTH;	
	}
}
// 绘制矩形
#ifndef COLOR
void WriteBlock(int x, int y, int height, int width, CHAR str[])
#else
void WriteBlock(int x, int y, int height, int width, CHAR str[], int attr[])
#endif
{
	int index = x + y * WIDTH;
	int i = 0;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (str[i] != JMP_CHAR) {
#ifndef COLOR
				screen[index + x] = str[i];
#else
				screen[index + x].Attributes = attr[i];
				screen[index + x].Char.AsciiChar = str[i];
#endif
			}
			i++;
		}
		index += WIDTH;
	}
}

// 清空缓冲区
void ClearConsoleBuffer(void)
{
#ifndef COLOR
	memset(screen, 0, WIDTH * HEIGHT);
#else
	memset(screen, 0, sizeof(screen));
#endif
}

void setConsoleColor(int attr)
{
	string_attr = attr;
}

void resetConsoleColor()
{
	string_attr = DEFAULT_STR_ATTR;
}