package org.elsys;

import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.concurrent.atomic.AtomicLong;

public class BlockingQueue<T> {
	private int capacity;
	private static AtomicLong producersCount = new AtomicLong(0);
	private Queue<T> queue = new LinkedList<T>();
	
	public BlockingQueue(int capacity) {
		this.capacity = capacity;
	}
	
	private boolean isFull() {
		return queue.size() >= capacity;
	}
	
	public synchronized void put(T task) throws InterruptedException {
		while (isFull()) {
			wait();
		}
		
		queue.add(task);
		notify();
	}
	
	public synchronized T take() throws InterruptedException {
		while(queue.isEmpty()) {
			wait();
		}
		
		T result = queue.poll();
		notify();
		return result;
	}
	
	public boolean offer(T task, long timeout) throws InterruptedException {
		long initialMilliseconds = System.currentTimeMillis();
		while(isFull()) {
			long currentMilliseconds = System.currentTimeMillis();
			if (currentMilliseconds - initialMilliseconds >= timeout) {
				return false;
			}
			
			wait();
		}
		
		if (currentMilliseconds - initialMilliseconds >= timeout) {
			return false;
		}
		
		return true;
	}
	
	public T poll(long timeout) {
		
	}
	
	public 
	
	public static void main(String[] args) {
		BlockingQueue<String> queue = new BlockingQueue<>(10);
		List<Thread> producers = new LinkedList<Thread>();
		
		for (int i = 0; i < 10; i++) {
			producers.add(new Thread(() -> {
				while(true) {
					try {
						String task = "task" + producersCount.incrementAndGet();
						System.out.println("Going to add task " + task);
						queue.put(task);
						System.out.println("Task " + task + " added!");
						
					} catch (Exception e) {
						e.printStackTrace();
					}
				}
			}));
			
		}
		
		for (Thread thread: producers) {
			thread.start();
		}
		
		List<Thread> consumers = new LinkedList<Thread>();
		for (int i = 0; i < 5; i++) {
			consumers.add(new Thread(() -> {
				while(true) {
					try {
						String task = "";
						Thread.sleep(2000);
						task = queue.take();
						System.err.println("task consumed " + task);
					} catch (Exception e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}	
				}
			}));
		}
		
		for (Thread thread: consumers) {
			thread.start();
		}
	}
}
