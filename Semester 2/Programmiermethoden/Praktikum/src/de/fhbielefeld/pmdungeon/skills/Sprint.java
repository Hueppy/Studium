package de.fhbielefeld.pmdungeon.skills;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.Input;
import de.fhbielefeld.pmdungeon.entities.Hero;

/** Sprintfähigkeit Verfügbar ab Level 2. */
public class Sprint extends Skill {
  private final Hero hero;

  public Sprint(Hero hero) {
    this.hero = hero;
  }

  @Override
  public int unlockedAt() {
    return 2;
  }

  @Override
  public void update() {
    hero.setSprinting(Gdx.input.isKeyPressed(Input.Keys.SHIFT_LEFT));
  }
}
