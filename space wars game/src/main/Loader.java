package main;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import sprites.Laser;
import sprites.Lives;
import sprites.ShieldPowerup;
import sprites.ShotSpeedPowerup;
import sprites.SineEnemy;
import sprites.Spaceship;
import sprites.Sprite;
import sprites.BasicEnemy;
import sprites.BasicShooter;
import sprites.Boss;
import sprites.EnemyLaserShot;

public class Loader {
	private final static float Y_COORDINAYE = -64;
	
	/**
	 * Create the appropriate sprite given a name and location.
	 * @param name	the name of the sprite
	 * @param x		the x position
	 * @param y		the y position
	 * @return		the sprite object
	 */
	public static Sprite createSprite(String name, float x, float y, int delay) {
		// based on what the name is find what type tile is and run that class
		try {
			switch (name) {
			case "Spaceship":
				return new Spaceship(x, y);
			case "Laser":
				return new Laser(x, y, delay);
			case "BasicEnemy":
				return new BasicEnemy(x, y, delay);
			case "BasicShooter":
				return new BasicShooter(x, y, delay);
			case "SineEnemy":
				return new SineEnemy(x, y, delay);
			case "Boss":
				return new Boss(x, y, delay);
			case "Lives":
				return new Lives(x, y);
			case "EnemyLaserShot":
				return new EnemyLaserShot(x, y, delay);
			case "ShotSpeedPowerup":
				return new ShotSpeedPowerup(x, y, delay);
			case "ShieldPowerup":
				return new ShieldPowerup(x, y, delay);
			}
			return null;
			
		} catch (Exception e) {
			e.printStackTrace();
			return null;
		}
	}
	
	/**
	 * adds Sprite to an arraylist.
	 * @return
	 */
	public static ArrayList<Sprite> addSprites(String filename) {
		ArrayList<Sprite> list = new ArrayList<>();
		
		list.add(createSprite("Spaceship", 480, 688, 0));
		
		// Open the file    
		try (BufferedReader reader = new BufferedReader(new FileReader(filename))) {
			String line;
					
			// Find the world size
			line = reader.readLine();
			String[] parts = line.split(",");
				
			// Loop over every line of the file
			while ((line = reader.readLine()) != null) {
				String name;
				int x;
				int delay;
						
				// Split the line into parts
				parts = line.split(",");
				int length = parts.length;
				
				if(length == 3) {
					name = parts[0];
					x = Integer.parseInt(parts[1]);
					delay = Integer.parseInt(parts[2]);
									
					// Create the sprite
					list.add(createSprite(name, x, Y_COORDINAYE, delay));
					
				}
			}
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
		return list;
	}
}
