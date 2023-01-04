# frozen_string_literal: true

# services for stripe
module StripeServiceLayer
    extend self 

    def price_generator(cd)
        m= cd.out_time
        n= cd.in_time 
        $price =  (((m-n)/1.hours).round)*100
        if $price < 100 
            $price = 100
        end
        return $price
    end

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
        after_completion: { type: 'redirect', redirect: { url: 'http://localhost:3000/homes/hello' } }
        )
        system('xdg-open', order.url)
    end
end



# def create
#     CreateCustomerDetailService.new(params[:customer_detail][:id]).call
#     @ud = CustomerDetail.new(ud_params)
#     @ud.slot.status = true
#     $price = price_generator(@ud)
    
#     if @ud.save && @ud.slot.save and @ud.name == current_user.name
#       UserDetailMailer.booking_confirmation(@ud, current_user, 'user').deliver_later
#       flash[:notice] = 'Successfully applied'
#       slot_payment($price)
#       redirect_to @ud
#     else
#       render 'new', status: :unprocessable_entity
#     end
#   rescue StandardError => e
#     flash[:notice] = e.message
#     redirect_to floors_path
#   end