describe('institution details', () => {
    beforeEach(() => {
        cy.visit('/institution/1')
    })

    it('shows details', () => {
        cy.get('.card-title').should('have.text', 'Institution A')
        cy.get('.card-text ul')
            .children('li')
            .invoke('text')
            .should("match", /^Campus A[1-3], 12345 Musterstadt/)
    })
})