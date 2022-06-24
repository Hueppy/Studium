using Microsoft.AspNetCore.Mvc;
using FHGuide.Shared.Models;
using FHGuide.Shared.Contexts;

namespace FHGuide.Api.Controllers;

[ApiController]
[Route("[controller]")]
public class ScheduleController : ControllerBase
{
	private readonly FHGuideContext DbContext;

    public ScheduleController(FHGuideContext dbContext)
    {
		this.DbContext = dbContext;
    }

	/// <summary>
	/// Get all schedules
	/// </summary>
	[HttpGet]
	public IEnumerable<Schedule> Get()
	{
		return this.DbContext.Schedules;
	}

	/// <summary>
	/// Create a new schedule
	/// </summary>
	[HttpPost]
	public async Task<int> Post(Schedule schedule)
	{
		schedule.ScheduleId = 0;
        var entry = await this.DbContext.Schedules.AddAsync(schedule);
        await this.DbContext.SaveChangesAsync();
        return entry.Entity.ScheduleId;
	}

	/// <summary>
	/// Update schedule with specified id
	/// </summary>
	[HttpPatch("{id}")]
	public async Task<ActionResult> Patch(int id, Schedule schedule)
	{
		if (!this.DbContext.Schedules.Any(x => x.ScheduleId == id)) {
            return NotFound();
        }
        schedule.ScheduleId = id;
        var entry = this.DbContext.Schedules.Update(schedule);
        await this.DbContext.SaveChangesAsync();
        return Ok();
	}

	/// <summary>
	/// Delete schedule with specified id
	/// </summary>
	[HttpDelete("{id}")]
	public async Task<ActionResult> Delete(int id)
	{
		var schedule = await this.DbContext.Schedules.FindAsync(id);
        if (schedule == null)
        {
            return NotFound();
        }    
        
        this.DbContext.Schedules.Remove(schedule);
        await this.DbContext.SaveChangesAsync();
        return Ok();
	}
}
