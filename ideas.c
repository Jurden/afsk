static int afsk_open(struct inode *inode, struct file *filp)
{
	if(filp->f_Flags & O_WRONLY) return 0;
	return ;//ERROR
}
static int afsk_write(struct inode *inode, struct file *filp)
{

}
static int afsk_release(struct inode *inode, struct file *filp)
{

}
static long afsk_ioctl(struct file *filp, uint cmd, ul arg)
{
	get_user((uint32_t _user *) arg);
}

