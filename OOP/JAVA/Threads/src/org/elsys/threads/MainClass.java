package org.elsys.threads;

public class MainClass {
	public static void main(String[] args) throws InterruptedException {
		Thread thread = new ThreadImplementation();
		thread.start();
		
		Thread thread2 = new Thread(new Runnable() {

			@Override
			public void run() {
				// TODO Auto-generated method stub
				
			}
		});
		//Thread.sleep(10);
		System.out.println("Exit from main");
	}
}
