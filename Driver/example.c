/**********************************************************************\
 *			===== example.c =====
 * Date: 2023/06/23
 * Auth: Guanyan Wang		
 * Desc:	
 * 	This program is use to practice writing driver in linux OS.
 *
\***********************************************************************/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

MODULE_LICENSE("Dual BSD/GPL");

static int example_open(struct inode *inode, struct file *filp){
	printk("<1> Example: open\n");
	return 0;
}

static int example_close(struct inode *inode, struct file *filp){
	printk("<1> Example: close\n");
	return 0;
}

static ssize_t example_read(struct file *filp, char *buf, size_t size, loff_t *f_pos){
	printk("<1> Example: read (size=%zu)\n", size);
	return 0;
}

static ssize_t example_write(struct file *filp, const char *buf, size_t size, loff_t *f_pos) {
	size_t pos;
	uint8_t byte;
	printk("<1> Example: write (size=%zu)\n", size);
	for (pos = 0; pos < size; ++pos){
		if (copy_from_user(&byte, buf + pos, 1) != 0){
			break;
		}
		printk("<1> Example: write (buf[%zu] = %02x)\n", pos, (unsigned)byte);
	}
	return pos;
}

static struct file_operations example_fops = {
	.open = example_open,
	.release = example_close,
	.read = example_read,
	.write = example_write,
};



#define EXAMPLE_MAJOR 60		// Major can be 60,61,62, if your driver is to publish, you need to find coresponding major ID on Docuementation/devices.txt
#define EXAMPLE_NAME "example"

static int example_init(void){
	int result;
	printk("<1> Example: init\n");

	/* register this driver as character device */
	result = register_chrdev(EXAMPLE_MAJOR, EXAMPLE_NAME, &example_fops);
	if (result < 0){
		printk("<1> Example: Failed to register character device\n");
		return result;
	}
	return 0;
}

static void example_exit(void){
	printk("<1> Example: exit\n");
	unregister_chrdev(EXAMPLE_MAJOR, EXAMPLE_NAME);
}




module_init(example_init);
module_exit(example_exit);

