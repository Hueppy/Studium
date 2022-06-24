package de.fhbielefeld.pmdungeon.entities;

import com.badlogic.gdx.graphics.Texture;
import de.fhbielefeld.pmdungeon.inventory.Inventory;

/** Implementierung eines Rucksack-Gegenstands, welche andere Gegenstände beinhalten kann. */
public class Bag<T extends Item> extends Item {
  private final Inventory<T> inventory;

  public Bag(Inventory<T> inventory) {
    this.inventory = inventory;
  }

  @Override
  protected Texture createTexture() {
    return new Texture("assets/frames/muddy_idle_anim_f0.png");
  }

  /** Zeigt das Inventar der Tasche. */
  @Override
  public void use(Character character) {
    this.inventory.show();
    if (character instanceof Hero) {
      ((Hero) character).pickup(this);
    }
  }

  @Override
  public String toString() {
    return String.format("Bag");
  }
}
