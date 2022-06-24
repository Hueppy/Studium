package de.fhbielefeld.pmdungeon.test.quests;

import de.fhbielefeld.pmdungeon.quests.ProgressionQuest;
import de.fhbielefeld.pmdungeon.quests.Quest;
import de.fhbielefeld.pmdungeon.quests.QuestTaker;
import java.util.List;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

/** Test für eine Fortschrittquest. */
public class ProgressionQuestTest {
  private QuestTakerMock taker;

  @Before
  public void setUp() throws Exception {
    this.taker = new QuestTakerMock();
  }

  @Test
  public void testProgressLevelExpectQuestFinished() {
    ProgressionQuest quest = new ProgressionQuest(10, List.of());
    quest.setTaker(taker);

    quest.update(null);

    Assert.assertTrue(taker.finished);
  }

  private class QuestTakerMock implements QuestTaker {
    public boolean finished = false;

    @Override
    public void finished(Quest quest) {
      this.finished = true;
    }
  }
}
