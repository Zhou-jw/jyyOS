N, Tp, Tc = 2, 2, 2 #2 pairs (), producer = 2, consumer = 2

def Tproduce(nm):
  while heap.mutex != 'Yes':
    sys_sched()
  heap.mutex = 'No'
  sys_sched()
  
  while not (heap.count < N):
    heap.blocked.append(nm)
    heap.mutex = 'Yes'
    sys_sched()
    while nm in heap.blocked:
      sys_sched()
    while heap.mutex != 'Yes':
      sys_sched()
    heap.mutex = 'No'
    sys_sched()

  heap.count += 1
  sys_sched()
  sys_write('(')
  sys_sched()
  heap.blocked = []
  sys_sched()
  heap.mutex = 'Yes'

def Tconsume(nm):
  while heap.mutex != 'Yes':
    sys_sched()
  heap.mutex = 'No'
  sys_sched()
  
  while not (heap.count > 0):
    heap.blocked.append(nm)
    heap.mutex = 'Yes'
    sys_sched()
    while nm in heap.blocked:
      sys_sched()
    while heap.mutex != 'Yes':
      sys_sched()
    heap.mutex = 'No'
    sys_sched()

  heap.count -= 1
  sys_sched()
  sys_write(')')
  sys_sched()
  heap.blocked = []
  sys_sched()
  heap.mutex = 'Yes'

def main():
  heap.count = 0
  heap.mutex = 'Yes'
  heap.blocked = []

  for i in range(Tp):
    sys_spawn(Tproduce, f'Tp{i+1}')
  for i in range(Tc):
    sys_spawn(Tconsume, f'Tc{i+1}')

# Outputs:
# (())
# ()()