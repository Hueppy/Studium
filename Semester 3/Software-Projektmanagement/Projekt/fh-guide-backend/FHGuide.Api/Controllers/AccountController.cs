using Microsoft.AspNetCore.Mvc;
using FHGuide.Shared.Models;
using FHGuide.Shared.Contexts;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Authorization;

namespace FHGuide.Api.Controllers;

[ApiController]
[Route("[controller]")]
public class AccountController : ControllerBase
{
	private readonly FHGuideContext dbContext;
    private readonly IPasswordHasher<Account> hasher;

    public AccountController(
        FHGuideContext dbContext,
        IPasswordHasher<Account> hasher)
    {
		this.dbContext = dbContext;
        this.hasher = hasher;
    }

	/// <summary>
	/// Get all accounts
	/// </summary>
	[HttpGet]
	public IEnumerable<Account> Get()
	{
		foreach (var account in this.dbContext.Accounts)
        {
            account.Password = string.Empty;
            yield return account;
        }
	}

	/// <summary>
	/// Get account with specified id
	/// </summary>
	/// <response code="404">Account could not be found</response>
	[HttpGet("{id}")]
	public async Task<ActionResult<Account>> Get(int id)
	{
		var item = await this.dbContext.Accounts.FindAsync(id);

		if (item == null)
		{
			return NotFound();
		}

        item.Password = string.Empty;

		return item;
	}

	/// <summary>
	/// Get schedule for account
	/// </summary>
	/// <response code="404">Account could not be found</response>
	[HttpGet("{id}/schedule")]
	public async Task<ActionResult<IEnumerable<Schedule>>> GetSchedule(int id)
	{
		var item = await this.dbContext.Accounts.FindAsync(id);

		if (item == null)
		{
			return NotFound();
		}

		return Ok(this.dbContext.Schedules.Where((x) => x.AccountId == id));
	}

	/// <summary>
	/// Create new account
	/// </summary>
    [AllowAnonymous]
	[HttpPost]
	public async Task Post(Account account)
	{
        account.AccountId = 0;
        account.Password = this.hasher.HashPassword(account, account.Password);
        account.CreateDate = DateTime.Now;
        
		await this.dbContext.Accounts.AddAsync(account);
		await this.dbContext.SaveChangesAsync();
	}

	/// <summary>
	/// Update account with specified id
	/// </summary>
	[HttpPatch("{id}")]
	public async Task Patch(int id, Account account)
	{
		account.AccountId = id;
        account.Password = this.hasher.HashPassword(account, account.Password);
		this.dbContext.Accounts.Update(account);
		await this.dbContext.SaveChangesAsync();
	}

	/// <summary>
	/// Deletes account with specified id
	/// </summary>
	[HttpDelete("{id}")]
	public async Task<ActionResult> Delete(int id)
	{
		var item = await this.dbContext.Accounts.FindAsync(id);

		if (item == null)
		{
			return NotFound();
		}

		this.dbContext.Accounts.Remove(item);
        await this.dbContext.SaveChangesAsync();
		return Ok();
	}
}
