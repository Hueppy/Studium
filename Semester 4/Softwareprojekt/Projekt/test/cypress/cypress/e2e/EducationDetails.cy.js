describe('education details', () => {
    beforeEach(() => {
        cy.visit('/education/1')
    })

    it('shows details', () => {
        cy.get('.card-header a')
            .should('have.text', 'Institution A')
            .should('have.attr', 'href')
        cy.get('.card-title').should('have.text', 'Bildungsangebot 1')
        cy.get('.card-text').should('have.text', 'Beschreibung Bildungsangebot 1')
    })
})