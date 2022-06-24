using Microsoft.AspNetCore.Mvc;
using FHGuide.Shared.Models;
using FHGuide.Shared.Contexts;
using Microsoft.EntityFrameworkCore;

namespace FHGuide.Api.Controllers;

[ApiController]
[Route("[controller]")]
public class CourseController : ControllerBase
{
	private readonly FHGuideContext DbContext;

    public CourseController(FHGuideContext dbContext)
    {
		this.DbContext = dbContext;
    }

	/// <summary>
	/// Get all courses
	/// </summary>
	[HttpGet]
	public IEnumerable<Course> Get()
	{
        return this.DbContext.Courses;
	}

	/// <summary>
	/// Get all appointments of course
	/// </summary>
	[HttpGet("{id}/appointment")]
	public IEnumerable<Appointment> GetAppointment(int id)
	{        
        return this.DbContext.Appointments.Where(x => x.CourseId == id);
	}

	/// <summary>
	/// Get all roadmap items of course
	/// </summary>
	[HttpGet("{id}/roadmap")]
	public IEnumerable<RoadmapItem> GetRoadmap(int id)
	{
        return this.DbContext.Roadmapitems.Where(x => x.CourseId == id);
	}

	/// <summary>
	/// Get all schedules of course
	/// </summary>
	[HttpGet("{id}/schedule")]
	public IEnumerable<Schedule?> GetSchedule(int id)
	{
        return this.DbContext.ScheduleCourses
            .Include(x => x.Schedule)
            .Where(x => x.CourseId == id)
            .Select(x => x.Schedule);
	}

	/// <summary>
	/// Get zoom link of course
	/// </summary>
	[HttpGet("{id}/zoom")]
	public async Task<Zoom?> GetZoom(int id)
	{
		return await this.DbContext.Zooms.Where(x => x.CourseId == id).FirstOrDefaultAsync();
	}

	/// <summary>
	/// Create a new course
	/// </summary>	
	[HttpPost]
	public async Task<int> Post(Course course)
    {
        course.CourseId = 0;
        var entry = await this.DbContext.Courses.AddAsync(course);
        await this.DbContext.SaveChangesAsync();

        return entry.Entity.CourseId;
	}

	/// <summary>
	/// Update course with specified id
	/// </summary>
	[HttpPatch("{id}")]
	public async Task Patch(int id, Course course)
	{
        course.CourseId = id;
        this.DbContext.Courses.Update(course);
        await this.DbContext.SaveChangesAsync();
	}

	/// <summary>
	/// Delete course with specified id
	/// </summary>
	[HttpDelete("{id}")]
	public async Task<ActionResult> Delete(int id)
    {
        var course = await this.DbContext.Courses.FindAsync(id);
        
		if (course == null)
		{
			return NotFound();
		}

		this.DbContext.Courses.Remove(course);
        await this.DbContext.SaveChangesAsync();
		return Ok();
	}
}
