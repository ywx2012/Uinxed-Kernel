// beep.c -- 板载蜂鸣器驱动（基于 GPL-3.0 开源协议）
// Copyright © 2020 ViudiraTech，保留所有权利。
// 源于 MicroFish 撰写于 2024-6-29.

/* 设置板载蜂鸣器状态 */
void system_beep(int hertz)
{
	int i;
	if (hertz == 0) {
		/* 如果音调（Hz）为0，则关闭板载蜂鸣器 */
		i = inb(0x61);					// 读取当前的板载蜂鸣器状态
		outb(0x61, i & 0x0d);			// 关闭板载蜂鸣器
	} else {
		/* 计算音调的频率并设置板载蜂鸣器 */
		i = 1193180000 / hertz;			// 计算所需的分频值
		outb(0x43, 0xb6);				// 发送命令以设置计时器2
		outb(0x42, i & 0xff);			// 发送分频值的低字节
		outb(0x42, i >> 8);				// 发送分频值的高字节
		i = inb(0x61);					// 读取当前板载蜂鸣器状态
		outb(0x61, (i | 0x03) & 0x0f);	// 打开板载蜂鸣器
	}
}
