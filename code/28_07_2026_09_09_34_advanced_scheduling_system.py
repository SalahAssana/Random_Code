import heapq
from typing import List, Tuple

class Task:
    def __init__(self, id: int, priority: int, duration: int):
        self.id = id
        self.priority = priority
        self.duration = duration

class SchedulingSystem:
    def __init__(self):
        self.tasks: List[Task] = []
        self.allocated_tasks: List[Tuple[int, int]] = []

    def add_task(self, task: Task):
        self.tasks.append(task)

    def schedule_tasks(self) -> List[Tuple[int, int]]:
        tasks_copy = sorted(self.tasks, key=lambda x: (x.priority, -x.duration))
        available_time = 0
        scheduled_tasks = []
        for task in tasks_copy:
            if task.duration > available_time:
                allocated_start_time = available_time
                allocated_end_time = allocated_start_time + task.duration
                self.allocated_tasks.append((task.id, allocated_start_time, allocated_end_time))
                available_time = allocated_end_time
            else:
                allocated_start_time = available_time
                allocated_end_time = available_time + task.duration
                self.allocated_tasks.append((task.id, allocated_start_time, allocated_end_time))
                available_time = allocated_end_time
        return [tuple(task) for task in self.allocated_tasks]

    def get_scheduled_tasks(self) -> List[Tuple[int, int]]:
        return [(start_time, end_time) for start_time, end_time in self.allocated_tasks]

if __name__ == '__main__':
    scheduling_system = SchedulingSystem()
    tasks = [
        Task(1, 3, 5),
        Task(2, 2, 4),
        Task(3, 1, 7),
        Task(4, 4, 6),
        Task(5, 3, 8)
    ]
    for task in tasks:
        scheduling_system.add_task(task)

    scheduled_tasks = scheduling_system.schedule_tasks()
    print("Scheduled Tasks:")
    for task in scheduled_tasks:
        print(f"Task {task[0]} allocated from {task[1]} to {task[2]}")