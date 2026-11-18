% Scheduling Algorithm Simulator

% Import necessary libraries
import java.util.*;

class Task {
    String name;
    int arrivalTime;
    int burstTime;

    public Task(String name, int arrivalTime, int burstTime) {
        this.name = name;
        this.arrivalTime = arrivalTime;
        this.burstTime = burstTime;
    }
}

class Scheduler {
    Task[] tasks;
    int currentTime;

    public Scheduler(Task[] tasks) {
        this.tasks = tasks;
        this.currentTime = 0;
    }

    public void FCFS() {
        for (Task task : tasks) {
            while (currentTime < task.arrivalTime) {
                currentTime++;
            }
            System.out.println("Task " + task.name + " starts at time " + currentTime);
            currentTime += task.burstTime;
        }
    }

    public void SJF() {
        Task shortestTask = null;
        for (Task task : tasks) {
            if ((shortestTask == null) || (task.burstTime < shortestTask.burstTime)) {
                shortestTask = task;
            }
        }
        currentTime = shortestTask.arrivalTime;
        while (true) {
            boolean foundShortest = false;
            for (Task task : tasks) {
                if ((task.arrivalTime <= currentTime) && (task.burstTime < shortestTask.burstTime)) {
                    shortestTask = task;
                    foundShortest = true;
                }
            }
            if (!foundShortest) break;
            System.out.println("Task " + shortestTask.name + " starts at time " + currentTime);
            currentTime += shortestTask.burstTime;
        }
    }

    public void PriorityScheduling() {
        Task[] tasksCopy = new Task[tasks.length];
        for (int i = 0; i < tasks.length; i++) {
            tasksCopy[i] = tasks[i];
        }
        Arrays.sort(tasksCopy, new Comparator<Task>() {
            @Override
            public int compare(Task t1, Task t2) {
                return Integer.compare(t2.burstTime, t1.burstTime);
            }
        });
        currentTime = 0;
        for (Task task : tasksCopy) {
            while (currentTime < task.arrivalTime) {
                currentTime++;
            }
            System.out.println("Task " + task.name + " starts at time " + currentTime);
            currentTime += task.burstTime;
        }
    }
}

public class Main {
    public static void main(String[] args) {
        Task[] tasks = new Task[4];
        tasks[0] = new Task("A", 1, 5);
        tasks[1] = new Task("B", 2, 3);
        tasks[2] = new Task("C", 3, 7);
        tasks[3] = new Task("D", 4, 2);

        Scheduler scheduler = new Scheduler(tasks);
        System.out.println("FCFS:");
        scheduler.FCFS();
        System.out.println("\nSJF:");
        scheduler.SJF();
        System.out.println("\nPriority Scheduling:");
        scheduler.PriorityScheduling();
    }
}