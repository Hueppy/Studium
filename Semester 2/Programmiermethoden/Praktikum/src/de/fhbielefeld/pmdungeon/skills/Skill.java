package de.fhbielefeld.pmdungeon.skills;

/** Basisklasse für einen Skill. */
public abstract class Skill {
  /**
   * Level ab dem die Fähigkeit verfügbar ist.
   *
   * @return Level
   */
  public abstract int unlockedAt();

  /** Update Methode der Fähigkeit. */
  public abstract void update();
}
