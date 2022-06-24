package de.fhbielefeld.pmdungeon.entities.traps;

import com.badlogic.gdx.graphics.Texture;
import de.fhbielefeld.pmdungeon.entities.Character;
import de.fhbielefeld.pmdungeon.vorgaben.graphic.Animation;
import de.fhbielefeld.pmdungeon.vorgaben.interfaces.IAnimatable;
import java.util.List;

/** Stachelfalle, welche dem Helden Schaden zufügt. */
public class Spikes extends Trap implements IAnimatable {
  private final Animation animation =
      new Animation(
          List.of(
              new Texture("assets/frames/floor_spikes_anim_f0.png"),
              new Texture("assets/frames/floor_spikes_anim_f1.png"),
              new Texture("assets/frames/floor_spikes_anim_f2.png"),
              new Texture("assets/frames/floor_spikes_anim_f3.png")),
          16);

  @Override
  public Animation getActiveAnimation() {
    return animation;
  }

  @Override
  public void activate(Character character) {
    character.damage(null, 2);
  }
}
