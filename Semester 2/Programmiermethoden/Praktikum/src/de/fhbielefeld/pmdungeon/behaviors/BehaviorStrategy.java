package de.fhbielefeld.pmdungeon.behaviors;

import de.fhbielefeld.pmdungeon.entities.Monster;

/** Basisklasse für eine Verhaltensstrategie. */
public abstract class BehaviorStrategy {
  protected final Monster monster;

  public BehaviorStrategy(Monster monster) {
    this.monster = monster;
  }

  public abstract void update();
}
