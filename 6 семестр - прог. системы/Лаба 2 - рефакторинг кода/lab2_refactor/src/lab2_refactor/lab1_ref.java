package lab2_refactor;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

/**
 * 
 * @author Ptakhova A.M.
 * @version 1.0.1
 * @since 18-02-2023
 *
 */


public class lab1_ref {

	
	/**
	 * 
	 * This main method 
	 * 
	 * @param args
	 * @throws IOException if entered number is not an integer
	 */
	public static void main(String[] args) throws IOException{
		// TODO Auto-generated method stub
		PrimeGener prg = new PrimeGener();
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		
		
		while (true)
		{
			System.out.print(
					"Select action:\n"
					+ "1. Get random number\n"
					+ "2. Get an array of random number\n"
					+ "3. Exit\n");
			
			String line = reader.readLine();
			int c;
			
			try {
				c = Integer.parseInt(line);
			} catch (NumberFormatException ignore) {
				System.out.println("Undefined command");
				continue;
			}
			if (c==1)
				System.out.println(prg.getRandomNumber());
			else if (c==2)
			{
				System.out.println("Enter the length of the array: ");
				int length;
				while (true)
				{
					line = reader.readLine();
					try
					{
						length = Integer.parseInt(line);
					}
					catch (NumberFormatException ignore)
					{
						System.out.println("The length must be a positive integer");
						continue;
					}
					
					if (length<=0)
					{
						System.out.println("The length must be a positive integer");
						continue;
					}
					else
					{
						break;
					}
					
				}
				
				int [] array = prg.getRandomArray(length) ;
				
				for (int v:array)
				{
					System.out.println(v);
				}
			}
			else if (c==3)
			{
				break;
			}
			else 
			{
				System.out.println("Undefined commands");
			}
			
		}
		
	}
	
	}
