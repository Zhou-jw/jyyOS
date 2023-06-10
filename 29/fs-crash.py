def main():
  # intially, file has a single block #1
  sys_bwrite('file.inode', 'file #1')
  sys_bwrite('used', '#1')
  sys_bwrite('#1', '1-old')
  sys_bwrite('#2', '2-garbage')
  sys_sync()

  # append a block #2 to the file

  sys_bwrite('file.inode', f'file #1 #2')
  sys_bwrite('used', '#1 #2')
  sys_bwrite(f'#1', f'1-new')
  sys_bwrite(f'#2', f'2-new')
  sys_crash()  # system crash

  # display file system state at crash recovery
  inode = sys_bread('file.inode')
  used = sys_bread('used')
  sys_write(f'{inode} | used {used} | ')
  for i in [1, 2]:
    b = sys_bread(f'#{i}')
    sys_write(f'{b} ')

# Outputs:
# file #1 #2 | used #1 #2 | 1-new 2-garbage
# file #1 #2 | used #1 #2 | 1-new 2-new
# file #1 #2 | used #1 #2 | 1-old 2-garbage
# file #1 #2 | used #1 #2 | 1-old 2-new
# file #1 #2 | used #1 | 1-new 2-garbage
# file #1 #2 | used #1 | 1-new 2-new
# file #1 #2 | used #1 | 1-old 2-garbage
# file #1 #2 | used #1 | 1-old 2-new
# file #1 | used #1 #2 | 1-new 2-garbage
# file #1 | used #1 #2 | 1-new 2-new
# file #1 | used #1 #2 | 1-old 2-garbage
# file #1 | used #1 #2 | 1-old 2-new
# file #1 | used #1 | 1-new 2-garbage
# file #1 | used #1 | 1-new 2-new
# file #1 | used #1 | 1-old 2-garbage
# file #1 | used #1 | 1-old 2-new