package de.fhbielefeld.pmdungeon.hud;

import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.Sprite;
import de.fhbielefeld.pmdungeon.inventory.Inventory;

/** Darstellung eines fremden Inventars. */
public class InventoryScreen extends Screen<Inventory> {
  private final Texture background = new Texture("assets/background/inventory.png");

  @Override
  protected Texture getBackground() {
    return background;
  }

  @Override
  protected void drawContents(Inventory object) {
    final int capacity = object.getCapacity();
    for (int i = 0; i < capacity; i++) {
      final float x = i % 5 + 1f;
      final float y = i / 5 + 2f;

      InventoryIcon icon = new InventoryIcon(object, i);

      Texture texture = icon.getTexture();
      Sprite sprite = new Sprite(texture);

      sprite.setSize(icon.getWidth(), icon.getHeight() / texture.getWidth());
      sprite.setPosition(x, y);
      sprite.draw(batch);
    }
  }
}
