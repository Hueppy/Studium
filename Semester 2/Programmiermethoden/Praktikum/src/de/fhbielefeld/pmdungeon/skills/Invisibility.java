package de.fhbielefeld.pmdungeon.skills;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.Input;
import de.fhbielefeld.pmdungeon.entities.Hero;
import java.util.Calendar;
import java.util.GregorianCalendar;

/** Unsichtbarkeitsfähigkeit Verfügbar ab Level 5. */
public class Invisibility extends Skill {
  private final Hero hero;
  private GregorianCalendar activatedAt;

  /** Erstellt ein Unsichtbarkeitsskill. */
  public Invisibility(Hero hero) {
    this.hero = hero;
    activatedAt = new GregorianCalendar();
    activatedAt.add(Calendar.MINUTE, -1);
  }

  /**
   * Skill wird ab Level 5 freigeschaltet.
   *
   * @return 5
   */
  @Override
  public int unlockedAt() {
    return 5;
  }

  @Override
  public void update() {
    final GregorianCalendar date = new GregorianCalendar();
    date.add(Calendar.SECOND, -20);
    if (activatedAt.before(date)) {
      hero.setVisible(true);
    }

    date.add(Calendar.SECOND, -40);
    if (activatedAt.before(date) && Gdx.input.isKeyJustPressed(Input.Keys.R)) {
      hero.setVisible(false);
      activatedAt = new GregorianCalendar();
    }
  }
}
