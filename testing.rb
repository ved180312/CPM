def slot_payment(price)
    require('stripe')
    Stripe.api_key = 'sk_test_51LucnKSIHsNyDSkgC7TG2qkTgSCN7TdIIsHIPrU2fXXY5bDYh0zhc6maJuMt74CrE3srdVdWkC4srEmdWrv9HWDN00JcbC5NAV'
    price = Stripe::Price.create({
                                   unit_amount: price * 100,
                                   currency: 'inr',
                                   product: 'prod_N4zVTLbPiO5Ea6'
                                 })
    order = Stripe::PaymentLink.create(
      line_items: [{ price: price.id, quantity: 1 }],
      after_completion: { type: 'redirect', redirect: { url: 'http://localhost:3000/thanks' } }
    )
    system('xdg-open', order.url)
end
slot_payment()