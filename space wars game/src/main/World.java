package main;

import java.util.ArrayList;

import org.newdawn.slick.Graphics;
import org.newdawn.slick.Image;
import org.newdawn.slick.Input;
import org.newdawn.slick.SlickException;

import sprites.Sprite;
import main.App;
import main.World;

public class World {
	public static final String BACKGROUND_PATH = "res/space.png";
	private static final float BACKGROUND_SCROLL_SPEED = 0.2f;
	private ArrayList<Sprite> sprites= new ArrayList<>();
	
	private float backgroundOffset = 0;
	private Image background;
	
	private static World world;
	
	/**
	 * Returns the created instance of the world.
	 * Constructor is private so that only one instance can ever exist.
	 * @return
	 */
	public static World getInstance() {
		if (world == null) {
			world = new World();
		}
		return world;
	}
	
	/**
	 * Adds a given sprite to the game list.
	 * @param sprite
	 */
	public void addSprite(Sprite sprite) {
		sprites.add(sprite);
	}
	/**
	 * replace sprite1 with sprite2
	 * @param sprite
	 */
	public void replaceSprite(Sprite sprite1, Sprite sprite2) {
		
		sprites.remove(sprite1);
		sprites.add(sprite2);
	}
	public World() {
		
		try {
			background = new Image(BACKGROUND_PATH);
		} catch (SlickException e) {
			e.printStackTrace();
		}
		
		sprites = Loader.addSprites("res/waves.txt");
		
		world = this;
	}

	/** Update the sprite state.
     * @param input the values input by user
     * @param delta Time passed since last frame (milliseconds).
     */
	public void update(Input input, int delta) {
		
		if (input.isKeyDown(Input.KEY_S)) {
			delta=delta*5;
			
		}
		// Update all sprites
		for (int i = 0; i < sprites.size(); ++i) {
			sprites.get(i).update(input, delta);
		}
		
		// Handle collisions
		for (Sprite sprite : sprites) {
			for (Sprite other : sprites) {
				if (sprite != other && sprite.getBoundingBox().intersects(other.getBoundingBox())) {
					sprite.contactSprite(other);
				}
			}
		}
		
		// Clean up inactive sprites
		for (int i = 0; i < sprites.size(); ++i) {
			if (sprites.get(i).getActive() == false) {
				sprites.remove(i);
				// decrement counter to make sure we don't miss any
				--i;
			}
		}
				
		backgroundOffset += BACKGROUND_SCROLL_SPEED * delta;
		backgroundOffset = backgroundOffset % background.getHeight();
		
	}
	
	/**
	 * Renders one step of the game.
	 */
	public void render(Graphics g) {
		// Tile the background image
		for (int i = 0; i < App.SCREEN_WIDTH; i += background.getWidth()) {
			for (int j = -background.getHeight() + (int)backgroundOffset; j < App.SCREEN_HEIGHT; j += background.getHeight()) {
				background.draw(i, j);
			}
		}
		for (Sprite sprite : sprites) {
			if (sprite != null) {
				sprite.render(g);
			}
		}
	}

}