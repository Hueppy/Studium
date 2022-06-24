package de.fhbielefeld.pmdungeon.entities;

import com.badlogic.gdx.graphics.Texture;

/** Implementierung eines Heiltrankes. */
public class Potion extends Item {
  private final int health = 100;

  @Override
  protected Texture createTexture() {
    return new Texture("assets/frames/flask_big_red.png");
  }

  /** Heilt den übergebenen Helden um die festgelegten Lebenspunkte. */
  @Override
  public void use(Character character) {
    character.restore(health);
    consumed = true;
  }

  @Override
  public String toString() {
    return String.format("Health Potion (%d hp)", health);
  }
}
